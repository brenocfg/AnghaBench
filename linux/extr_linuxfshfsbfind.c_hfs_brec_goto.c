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
typedef  scalar_t__ u16 ;
struct hfs_find_data {int record; struct hfs_bnode* bnode; int /*<<< orphan*/  key; scalar_t__ entrylength; scalar_t__ entryoffset; scalar_t__ keylength; scalar_t__ keyoffset; } ;
struct hfs_btree {int dummy; } ;
struct hfs_bnode {int num_recs; int prev; int next; struct hfs_btree* tree; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 int PTR_ERR (struct hfs_bnode*) ; 
 struct hfs_bnode* hfs_bnode_find (struct hfs_btree*,int) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_bnode_read (struct hfs_bnode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ hfs_brec_keylen (struct hfs_bnode*,int) ; 
 scalar_t__ hfs_brec_lenoff (struct hfs_bnode*,int,scalar_t__*) ; 

int hfs_brec_goto(struct hfs_find_data *fd, int cnt)
{
	struct hfs_btree *tree;
	struct hfs_bnode *bnode;
	int idx, res = 0;
	u16 off, len, keylen;

	bnode = fd->bnode;
	tree = bnode->tree;

	if (cnt < 0) {
		cnt = -cnt;
		while (cnt > fd->record) {
			cnt -= fd->record + 1;
			fd->record = bnode->num_recs - 1;
			idx = bnode->prev;
			if (!idx) {
				res = -ENOENT;
				goto out;
			}
			hfs_bnode_put(bnode);
			bnode = hfs_bnode_find(tree, idx);
			if (IS_ERR(bnode)) {
				res = PTR_ERR(bnode);
				bnode = NULL;
				goto out;
			}
		}
		fd->record -= cnt;
	} else {
		while (cnt >= bnode->num_recs - fd->record) {
			cnt -= bnode->num_recs - fd->record;
			fd->record = 0;
			idx = bnode->next;
			if (!idx) {
				res = -ENOENT;
				goto out;
			}
			hfs_bnode_put(bnode);
			bnode = hfs_bnode_find(tree, idx);
			if (IS_ERR(bnode)) {
				res = PTR_ERR(bnode);
				bnode = NULL;
				goto out;
			}
		}
		fd->record += cnt;
	}

	len = hfs_brec_lenoff(bnode, fd->record, &off);
	keylen = hfs_brec_keylen(bnode, fd->record);
	if (keylen == 0) {
		res = -EINVAL;
		goto out;
	}
	fd->keyoffset = off;
	fd->keylength = keylen;
	fd->entryoffset = off + keylen;
	fd->entrylength = len - keylen;
	hfs_bnode_read(bnode, fd->key, off, keylen);
out:
	fd->bnode = bnode;
	return res;
}