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
typedef  int u64 ;
struct btrfs_block_rsv {int size; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 calc_global_rsv_need_space(struct btrfs_block_rsv *global)
{
	return (global->size << 1);
}