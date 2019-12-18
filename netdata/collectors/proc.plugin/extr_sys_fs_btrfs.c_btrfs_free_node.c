#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {struct TYPE_6__* id; struct TYPE_6__* label; TYPE_2__* disks; struct TYPE_6__* allocation_system_total_bytes_filename; struct TYPE_6__* allocation_system_bytes_used_filename; struct TYPE_6__* allocation_metadata_total_bytes_filename; struct TYPE_6__* allocation_metadata_bytes_used_filename; struct TYPE_6__* allocation_data_total_bytes_filename; struct TYPE_6__* allocation_data_bytes_used_filename; scalar_t__ st_allocation_system; scalar_t__ st_allocation_metadata; scalar_t__ st_allocation_data; scalar_t__ st_allocation_disks; } ;
typedef  TYPE_1__ BTRFS_NODE ;
typedef  TYPE_2__ BTRFS_DISK ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_free_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_is_obsolete (scalar_t__) ; 

__attribute__((used)) static inline void btrfs_free_node(BTRFS_NODE *node) {
    // info("BTRFS: destroying '%s'", node->id);

    if(node->st_allocation_disks)
        rrdset_is_obsolete(node->st_allocation_disks);

    if(node->st_allocation_data)
        rrdset_is_obsolete(node->st_allocation_data);

    if(node->st_allocation_metadata)
        rrdset_is_obsolete(node->st_allocation_metadata);

    if(node->st_allocation_system)
        rrdset_is_obsolete(node->st_allocation_system);

    freez(node->allocation_data_bytes_used_filename);
    freez(node->allocation_data_total_bytes_filename);

    freez(node->allocation_metadata_bytes_used_filename);
    freez(node->allocation_metadata_total_bytes_filename);

    freez(node->allocation_system_bytes_used_filename);
    freez(node->allocation_system_total_bytes_filename);

    while(node->disks) {
        BTRFS_DISK *d = node->disks;
        node->disks = node->disks->next;
        btrfs_free_disk(d);
    }

    freez(node->label);
    freez(node->id);
    freez(node);
}