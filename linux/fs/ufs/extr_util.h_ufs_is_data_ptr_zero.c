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
struct ufs_sb_private_info {scalar_t__ fs_magic; } ;
typedef  scalar_t__ __fs64 ;
typedef  scalar_t__ __fs32 ;

/* Variables and functions */
 scalar_t__ UFS2_MAGIC ; 

__attribute__((used)) static inline int ufs_is_data_ptr_zero(struct ufs_sb_private_info *uspi,
				       void *p)
{
	if (uspi->fs_magic == UFS2_MAGIC)
		return *(__fs64 *)p == 0;
	else
		return *(__fs32 *)p == 0;
}