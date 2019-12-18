#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lfs1_disk_superblock {void* version; void* block_count; void* block_size; void** root; } ;

/* Variables and functions */
 void* lfs1_tole32 (void*) ; 

__attribute__((used)) static void lfs1_superblock_tole32(struct lfs1_disk_superblock *d) {
    d->root[0]     = lfs1_tole32(d->root[0]);
    d->root[1]     = lfs1_tole32(d->root[1]);
    d->block_size  = lfs1_tole32(d->block_size);
    d->block_count = lfs1_tole32(d->block_count);
    d->version     = lfs1_tole32(d->version);
}