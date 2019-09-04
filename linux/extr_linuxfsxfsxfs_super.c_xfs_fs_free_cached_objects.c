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
struct super_block {int dummy; } ;
struct shrink_control {int /*<<< orphan*/  nr_to_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_M (struct super_block*) ; 
 long xfs_reclaim_inodes_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
xfs_fs_free_cached_objects(
	struct super_block	*sb,
	struct shrink_control	*sc)
{
	return xfs_reclaim_inodes_nr(XFS_M(sb), sc->nr_to_scan);
}