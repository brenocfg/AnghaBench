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
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dptrs (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_nchildren (struct nilfs_btree_node*,int) ; 

__attribute__((used)) static void nilfs_btree_node_insert(struct nilfs_btree_node *node, int index,
				    __u64 key, __u64 ptr, int ncmax)
{
	__le64 *dkeys;
	__le64 *dptrs;
	int nchildren;

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	nchildren = nilfs_btree_node_get_nchildren(node);
	if (index < nchildren) {
		memmove(dkeys + index + 1, dkeys + index,
			(nchildren - index) * sizeof(*dkeys));
		memmove(dptrs + index + 1, dptrs + index,
			(nchildren - index) * sizeof(*dptrs));
	}
	dkeys[index] = cpu_to_le64(key);
	dptrs[index] = cpu_to_le64(ptr);
	nchildren++;
	nilfs_btree_node_set_nchildren(node, nchildren);
}