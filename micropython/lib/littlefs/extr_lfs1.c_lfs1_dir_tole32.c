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
struct lfs1_disk_dir {void** tail; void* size; void* rev; } ;

/* Variables and functions */
 void* lfs1_tole32 (void*) ; 

__attribute__((used)) static void lfs1_dir_tole32(struct lfs1_disk_dir *d) {
    d->rev     = lfs1_tole32(d->rev);
    d->size    = lfs1_tole32(d->size);
    d->tail[0] = lfs1_tole32(d->tail[0]);
    d->tail[1] = lfs1_tole32(d->tail[1]);
}