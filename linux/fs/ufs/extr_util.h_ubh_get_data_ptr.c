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
typedef  int /*<<< orphan*/  u64 ;
struct ufs_sb_private_info {scalar_t__ fs_magic; } ;
struct ufs_buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ UFS2_MAGIC ; 
 void* ubh_get_addr32 (struct ufs_buffer_head*,int /*<<< orphan*/ ) ; 
 void* ubh_get_addr64 (struct ufs_buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *ubh_get_data_ptr(struct ufs_sb_private_info *uspi,
				     struct ufs_buffer_head *ubh,
				     u64 blk)
{
	if (uspi->fs_magic == UFS2_MAGIC)
		return ubh_get_addr64(ubh, blk);
	else
		return ubh_get_addr32(ubh, blk);
}