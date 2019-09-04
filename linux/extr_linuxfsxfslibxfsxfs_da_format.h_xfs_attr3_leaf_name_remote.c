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
typedef  int /*<<< orphan*/  xfs_attr_leafblock_t ;
typedef  int /*<<< orphan*/  xfs_attr_leaf_name_remote_t ;

/* Variables and functions */
 scalar_t__ xfs_attr3_leaf_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline xfs_attr_leaf_name_remote_t *
xfs_attr3_leaf_name_remote(xfs_attr_leafblock_t *leafp, int idx)
{
	return (xfs_attr_leaf_name_remote_t *)xfs_attr3_leaf_name(leafp, idx);
}