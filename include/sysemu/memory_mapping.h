/*
 * QEMU memory mapping
 *
 * Copyright Fujitsu, Corp. 2011, 2012
 *
 * Authors:
 *     Wen Congyang <wency@cn.fujitsu.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef MEMORY_MAPPING_H
#define MEMORY_MAPPING_H

#include "qemu/queue.h"
#include "qemu/typedefs.h"

/* The physical and virtual address in the memory mapping are contiguous. */
typedef struct MemoryMapping {
    hwaddr phys_addr;
    target_ulong virt_addr;
    ram_addr_t length;
    QTAILQ_ENTRY(MemoryMapping) next;
} MemoryMapping;

struct MemoryMappingList {
    unsigned int num;
    MemoryMapping *last_mapping;
    QTAILQ_HEAD(, MemoryMapping) head;
};

/*
 * add or merge the memory region [phys_addr, phys_addr + length) into the
 * memory mapping's list. The region's virtual address starts with virt_addr,
 * and is contiguous. The list is sorted by phys_addr.
 */
void memory_mapping_list_add_merge_sorted(MemoryMappingList *list,
                                          hwaddr phys_addr,
                                          hwaddr virt_addr,
                                          ram_addr_t length);

void memory_mapping_list_free(MemoryMappingList *list);

void memory_mapping_list_init(MemoryMappingList *list);

void qemu_get_guest_memory_mapping(MemoryMappingList *list, Error **errp);

/* get guest's memory mapping without do paging(virtual address is 0). */
void qemu_get_guest_simple_memory_mapping(MemoryMappingList *list);

void memory_mapping_filter(MemoryMappingList *list, int64_t begin,
                           int64_t length);

#endif
