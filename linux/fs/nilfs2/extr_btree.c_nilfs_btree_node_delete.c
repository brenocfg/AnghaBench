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
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dptrs (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_nchildren (struct nilfs_btree_node*,int) ; 

__attribute__((used)) static void nilfs_btree_node_delete(struct nilfs_btree_node *node, int index,
				    __u64 *keyp, __u64 *ptrp, int ncmax)
{
	__u64 key;
	__u64 ptr;
	__le64 *dkeys;
	__le64 *dptrs;
	int nchildren;

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	key = le64_to_cpu(dkeys[index]);
	ptr = le64_to_cpu(dptrs[index]);
	nchildren = nilfs_btree_node_get_nchildren(node);
	if (keyp != NULL)
		*keyp = key;
	if (ptrp != NULL)
		*ptrp = ptr;

	if (index < nchildren - 1) {
		memmove(dkeys + index, dkeys + index + 1,
			(nchildren - index - 1) * sizeof(*dkeys));
		memmove(dptrs + index, dptrs + index + 1,
			(nchildren - index - 1) * sizeof(*dptrs));
	}
	nchildren--;
	nilfs_btree_node_set_nchildren(node, nchildren);
}