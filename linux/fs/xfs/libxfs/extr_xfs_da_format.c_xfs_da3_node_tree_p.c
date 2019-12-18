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
struct xfs_da_node_entry {int dummy; } ;
struct xfs_da_intnode {int dummy; } ;
struct xfs_da3_intnode {struct xfs_da_node_entry* __btree; } ;

/* Variables and functions */

__attribute__((used)) static struct xfs_da_node_entry *
xfs_da3_node_tree_p(struct xfs_da_intnode *dap)
{
	return ((struct xfs_da3_intnode *)dap)->__btree;
}