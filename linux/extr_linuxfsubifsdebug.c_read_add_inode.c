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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {unsigned long len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_ino_node {int dummy; } ;
struct ubifs_info {int dummy; } ;
struct fsck_inode {int dummy; } ;
struct fsck_data {int dummy; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct fsck_inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct fsck_inode*) ; 
 unsigned long PTR_ERR (struct fsck_inode*) ; 
 unsigned long UBIFS_INO_NODE_SZ ; 
 struct fsck_inode* add_inode (struct ubifs_info*,struct fsck_data*,struct ubifs_ino_node*) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ubifs_ino_node*) ; 
 struct ubifs_ino_node* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 struct fsck_inode* search_inode (struct fsck_data*,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,unsigned long,...) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 
 int ubifs_tnc_read_node (struct ubifs_info*,struct ubifs_zbranch*,struct ubifs_ino_node*) ; 

__attribute__((used)) static struct fsck_inode *read_add_inode(struct ubifs_info *c,
					 struct fsck_data *fsckd, ino_t inum)
{
	int n, err;
	union ubifs_key key;
	struct ubifs_znode *znode;
	struct ubifs_zbranch *zbr;
	struct ubifs_ino_node *ino;
	struct fsck_inode *fscki;

	fscki = search_inode(fsckd, inum);
	if (fscki)
		return fscki;

	ino_key_init(c, &key, inum);
	err = ubifs_lookup_level0(c, &key, &znode, &n);
	if (!err) {
		ubifs_err(c, "inode %lu not found in index", (unsigned long)inum);
		return ERR_PTR(-ENOENT);
	} else if (err < 0) {
		ubifs_err(c, "error %d while looking up inode %lu",
			  err, (unsigned long)inum);
		return ERR_PTR(err);
	}

	zbr = &znode->zbranch[n];
	if (zbr->len < UBIFS_INO_NODE_SZ) {
		ubifs_err(c, "bad node %lu node length %d",
			  (unsigned long)inum, zbr->len);
		return ERR_PTR(-EINVAL);
	}

	ino = kmalloc(zbr->len, GFP_NOFS);
	if (!ino)
		return ERR_PTR(-ENOMEM);

	err = ubifs_tnc_read_node(c, zbr, ino);
	if (err) {
		ubifs_err(c, "cannot read inode node at LEB %d:%d, error %d",
			  zbr->lnum, zbr->offs, err);
		kfree(ino);
		return ERR_PTR(err);
	}

	fscki = add_inode(c, fsckd, ino);
	kfree(ino);
	if (IS_ERR(fscki)) {
		ubifs_err(c, "error %ld while adding inode %lu node",
			  PTR_ERR(fscki), (unsigned long)inum);
		return fscki;
	}

	return fscki;
}