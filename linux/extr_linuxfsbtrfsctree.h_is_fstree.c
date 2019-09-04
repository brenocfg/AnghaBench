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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 scalar_t__ BTRFS_FS_TREE_OBJECTID ; 
 int /*<<< orphan*/  btrfs_qgroup_level (scalar_t__) ; 

__attribute__((used)) static inline int is_fstree(u64 rootid)
{
	if (rootid == BTRFS_FS_TREE_OBJECTID ||
	    ((s64)rootid >= (s64)BTRFS_FIRST_FREE_OBJECTID &&
	      !btrfs_qgroup_level(rootid)))
		return 1;
	return 0;
}