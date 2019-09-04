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
struct nilfs_btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dptrs (struct nilfs_btree_node*,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_flags (struct nilfs_btree_node*,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_level (struct nilfs_btree_node*,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_nchildren (struct nilfs_btree_node*,int) ; 

__attribute__((used)) static void nilfs_btree_node_init(struct nilfs_btree_node *node, int flags,
				  int level, int nchildren, int ncmax,
				  const __u64 *keys, const __u64 *ptrs)
{
	__le64 *dkeys;
	__le64 *dptrs;
	int i;

	nilfs_btree_node_set_flags(node, flags);
	nilfs_btree_node_set_level(node, level);
	nilfs_btree_node_set_nchildren(node, nchildren);

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	for (i = 0; i < nchildren; i++) {
		dkeys[i] = cpu_to_le64(keys[i]);
		dptrs[i] = cpu_to_le64(ptrs[i]);
	}
}