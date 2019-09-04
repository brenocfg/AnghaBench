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
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XFS_M (struct super_block*) ; 
 long xfs_reclaim_inodes_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
xfs_fs_nr_cached_objects(
	struct super_block	*sb,
	struct shrink_control	*sc)
{
	/* Paranoia: catch incorrect calls during mount setup or teardown */
	if (WARN_ON_ONCE(!sb->s_fs_info))
		return 0;
	return xfs_reclaim_inodes_count(XFS_M(sb));
}