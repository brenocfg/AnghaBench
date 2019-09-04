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
typedef  int /*<<< orphan*/  xfs_attr_leaf_name_remote_t ;
typedef  scalar_t__ uint ;
typedef  int nlen ;

/* Variables and functions */
 int XFS_ATTR_LEAF_NAME_ALIGN ; 

__attribute__((used)) static inline int xfs_attr_leaf_entsize_remote(int nlen)
{
	return ((uint)sizeof(xfs_attr_leaf_name_remote_t) - 1 + (nlen) + \
		XFS_ATTR_LEAF_NAME_ALIGN - 1) & ~(XFS_ATTR_LEAF_NAME_ALIGN - 1);
}