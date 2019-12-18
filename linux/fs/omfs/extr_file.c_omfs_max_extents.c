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
typedef  int u32 ;
struct omfs_sb_info {int s_sys_blocksize; } ;
struct omfs_extent_entry {int dummy; } ;
struct omfs_extent {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 omfs_max_extents(struct omfs_sb_info *sbi, int offset)
{
	return (sbi->s_sys_blocksize - offset -
		sizeof(struct omfs_extent)) /
		sizeof(struct omfs_extent_entry) + 1;
}