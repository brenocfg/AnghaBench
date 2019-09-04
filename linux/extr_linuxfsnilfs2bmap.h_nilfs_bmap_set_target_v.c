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
struct nilfs_bmap {void* b_last_allocated_ptr; void* b_last_allocated_key; } ;
typedef  void* __u64 ;

/* Variables and functions */

__attribute__((used)) static inline void nilfs_bmap_set_target_v(struct nilfs_bmap *bmap, __u64 key,
					   __u64 ptr)
{
	bmap->b_last_allocated_key = key;
	bmap->b_last_allocated_ptr = ptr;
}