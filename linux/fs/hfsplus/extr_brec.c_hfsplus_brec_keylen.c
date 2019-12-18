#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct hfs_bnode {scalar_t__ type; TYPE_1__* tree; } ;
struct TYPE_2__ {int attributes; scalar_t__ cnid; int max_key_len; int node_size; } ;

/* Variables and functions */
 scalar_t__ HFSPLUS_ATTR_CNID ; 
 scalar_t__ HFS_NODE_INDEX ; 
 scalar_t__ HFS_NODE_LEAF ; 
 int HFS_TREE_VARIDXKEYS ; 
 int hfs_bnode_read_u16 (struct hfs_bnode*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

u16 hfs_brec_keylen(struct hfs_bnode *node, u16 rec)
{
	u16 retval, recoff;

	if (node->type != HFS_NODE_INDEX && node->type != HFS_NODE_LEAF)
		return 0;

	if ((node->type == HFS_NODE_INDEX) &&
	   !(node->tree->attributes & HFS_TREE_VARIDXKEYS) &&
	   (node->tree->cnid != HFSPLUS_ATTR_CNID)) {
		retval = node->tree->max_key_len + 2;
	} else {
		recoff = hfs_bnode_read_u16(node,
			node->tree->node_size - (rec + 1) * 2);
		if (!recoff)
			return 0;
		if (recoff > node->tree->node_size - 2) {
			pr_err("recoff %d too large\n", recoff);
			return 0;
		}

		retval = hfs_bnode_read_u16(node, recoff) + 2;
		if (retval > node->tree->max_key_len + 2) {
			pr_err("keylen %d too large\n",
				retval);
			retval = 0;
		}
	}
	return retval;
}