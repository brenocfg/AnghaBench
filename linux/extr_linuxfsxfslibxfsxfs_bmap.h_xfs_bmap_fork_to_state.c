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

/* Variables and functions */
 int BMAP_ATTRFORK ; 
 int BMAP_COWFORK ; 
#define  XFS_ATTR_FORK 129 
#define  XFS_COW_FORK 128 

__attribute__((used)) static inline int xfs_bmap_fork_to_state(int whichfork)
{
	switch (whichfork) {
	case XFS_ATTR_FORK:
		return BMAP_ATTRFORK;
	case XFS_COW_FORK:
		return BMAP_COWFORK;
	default:
		return 0;
	}
}