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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BTREE_LEVEL_NODE_MIN ; 
 scalar_t__ nilfs_btree_node_get_key (struct nilfs_btree_node const*,int) ; 
 scalar_t__ nilfs_btree_node_get_level (struct nilfs_btree_node const*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node const*) ; 

__attribute__((used)) static int nilfs_btree_node_lookup(const struct nilfs_btree_node *node,
				   __u64 key, int *indexp)
{
	__u64 nkey;
	int index, low, high, s;

	/* binary search */
	low = 0;
	high = nilfs_btree_node_get_nchildren(node) - 1;
	index = 0;
	s = 0;
	while (low <= high) {
		index = (low + high) / 2;
		nkey = nilfs_btree_node_get_key(node, index);
		if (nkey == key) {
			s = 0;
			goto out;
		} else if (nkey < key) {
			low = index + 1;
			s = -1;
		} else {
			high = index - 1;
			s = 1;
		}
	}

	/* adjust index */
	if (nilfs_btree_node_get_level(node) > NILFS_BTREE_LEVEL_NODE_MIN) {
		if (s > 0 && index > 0)
			index--;
	} else if (s < 0)
		index++;

 out:
	*indexp = index;

	return s == 0;
}