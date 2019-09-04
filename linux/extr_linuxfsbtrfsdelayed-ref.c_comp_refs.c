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
struct btrfs_delayed_ref_node {scalar_t__ type; scalar_t__ seq; } ;

/* Variables and functions */
 scalar_t__ BTRFS_SHARED_BLOCK_REF_KEY ; 
 scalar_t__ BTRFS_TREE_BLOCK_REF_KEY ; 
 int /*<<< orphan*/  btrfs_delayed_node_to_data_ref (struct btrfs_delayed_ref_node*) ; 
 int /*<<< orphan*/  btrfs_delayed_node_to_tree_ref (struct btrfs_delayed_ref_node*) ; 
 int comp_data_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int comp_tree_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comp_refs(struct btrfs_delayed_ref_node *ref1,
		     struct btrfs_delayed_ref_node *ref2,
		     bool check_seq)
{
	int ret = 0;

	if (ref1->type < ref2->type)
		return -1;
	if (ref1->type > ref2->type)
		return 1;
	if (ref1->type == BTRFS_TREE_BLOCK_REF_KEY ||
	    ref1->type == BTRFS_SHARED_BLOCK_REF_KEY)
		ret = comp_tree_refs(btrfs_delayed_node_to_tree_ref(ref1),
				     btrfs_delayed_node_to_tree_ref(ref2));
	else
		ret = comp_data_refs(btrfs_delayed_node_to_data_ref(ref1),
				     btrfs_delayed_node_to_data_ref(ref2));
	if (ret)
		return ret;
	if (check_seq) {
		if (ref1->seq < ref2->seq)
			return -1;
		if (ref1->seq > ref2->seq)
			return 1;
	}
	return 0;
}