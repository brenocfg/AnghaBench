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
struct hfs_find_data {int record; int keylength; struct hfs_bnode* bnode; int /*<<< orphan*/  search_key; int /*<<< orphan*/  keyoffset; struct hfs_btree* tree; } ;
struct hfs_btree {int attributes; scalar_t__ cnid; int max_key_len; int node_size; scalar_t__ root; } ;
struct hfs_bnode {int num_recs; scalar_t__ parent; int /*<<< orphan*/  this; } ;
typedef  int /*<<< orphan*/  cnid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_MOD ; 
 int ENOENT ; 
 scalar_t__ HFSPLUS_ATTR_CNID ; 
 int HFS_TREE_VARIDXKEYS ; 
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 int PTR_ERR (struct hfs_bnode*) ; 
 int /*<<< orphan*/  __hfs_brec_find (struct hfs_bnode*,struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_copy (struct hfs_bnode*,int /*<<< orphan*/ ,struct hfs_bnode*,int,int) ; 
 int /*<<< orphan*/  hfs_bnode_dump (struct hfs_bnode*) ; 
 void* hfs_bnode_find (struct hfs_btree*,scalar_t__) ; 
 int /*<<< orphan*/  hfs_bnode_move (struct hfs_bnode*,int,int,int) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_bnode_read_key (struct hfs_bnode*,int /*<<< orphan*/ ,int) ; 
 int hfs_bnode_read_u16 (struct hfs_bnode*,int) ; 
 struct hfs_bnode* hfs_bnode_split (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_bnode_write_u16 (struct hfs_bnode*,int,int) ; 
 int /*<<< orphan*/  hfs_brec_insert (struct hfs_find_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hfs_btree_inc_height (struct hfs_btree*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hfs_find_rec_by_key ; 

__attribute__((used)) static int hfs_brec_update_parent(struct hfs_find_data *fd)
{
	struct hfs_btree *tree;
	struct hfs_bnode *node, *new_node, *parent;
	int newkeylen, diff;
	int rec, rec_off, end_rec_off;
	int start_off, end_off;

	tree = fd->tree;
	node = fd->bnode;
	new_node = NULL;
	if (!node->parent)
		return 0;

again:
	parent = hfs_bnode_find(tree, node->parent);
	if (IS_ERR(parent))
		return PTR_ERR(parent);
	__hfs_brec_find(parent, fd, hfs_find_rec_by_key);
	if (fd->record < 0)
		return -ENOENT;
	hfs_bnode_dump(parent);
	rec = fd->record;

	/* size difference between old and new key */
	if ((tree->attributes & HFS_TREE_VARIDXKEYS) ||
				(tree->cnid == HFSPLUS_ATTR_CNID))
		newkeylen = hfs_bnode_read_u16(node, 14) + 2;
	else
		fd->keylength = newkeylen = tree->max_key_len + 2;
	hfs_dbg(BNODE_MOD, "update_rec: %d, %d, %d\n",
		rec, fd->keylength, newkeylen);

	rec_off = tree->node_size - (rec + 2) * 2;
	end_rec_off = tree->node_size - (parent->num_recs + 1) * 2;
	diff = newkeylen - fd->keylength;
	if (!diff)
		goto skip;
	if (diff > 0) {
		end_off = hfs_bnode_read_u16(parent, end_rec_off);
		if (end_rec_off - end_off < diff) {

			hfs_dbg(BNODE_MOD, "splitting index node\n");
			fd->bnode = parent;
			new_node = hfs_bnode_split(fd);
			if (IS_ERR(new_node))
				return PTR_ERR(new_node);
			parent = fd->bnode;
			rec = fd->record;
			rec_off = tree->node_size - (rec + 2) * 2;
			end_rec_off = tree->node_size -
				(parent->num_recs + 1) * 2;
		}
	}

	end_off = start_off = hfs_bnode_read_u16(parent, rec_off);
	hfs_bnode_write_u16(parent, rec_off, start_off + diff);
	start_off -= 4;	/* move previous cnid too */

	while (rec_off > end_rec_off) {
		rec_off -= 2;
		end_off = hfs_bnode_read_u16(parent, rec_off);
		hfs_bnode_write_u16(parent, rec_off, end_off + diff);
	}
	hfs_bnode_move(parent, start_off + diff, start_off,
		       end_off - start_off);
skip:
	hfs_bnode_copy(parent, fd->keyoffset, node, 14, newkeylen);
	hfs_bnode_dump(parent);

	hfs_bnode_put(node);
	node = parent;

	if (new_node) {
		__be32 cnid;

		if (!new_node->parent) {
			hfs_btree_inc_height(tree);
			new_node->parent = tree->root;
		}
		fd->bnode = hfs_bnode_find(tree, new_node->parent);
		/* create index key and entry */
		hfs_bnode_read_key(new_node, fd->search_key, 14);
		cnid = cpu_to_be32(new_node->this);

		__hfs_brec_find(fd->bnode, fd, hfs_find_rec_by_key);
		hfs_brec_insert(fd, &cnid, sizeof(cnid));
		hfs_bnode_put(fd->bnode);
		hfs_bnode_put(new_node);

		if (!rec) {
			if (new_node == node)
				goto out;
			/* restore search_key */
			hfs_bnode_read_key(node, fd->search_key, 14);
		}
		new_node = NULL;
	}

	if (!rec && node->parent)
		goto again;
out:
	fd->bnode = node;
	return 0;
}