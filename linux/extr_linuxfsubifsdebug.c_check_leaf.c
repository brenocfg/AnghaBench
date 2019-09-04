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
struct ubifs_zbranch {scalar_t__ len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; int /*<<< orphan*/  key; } ;
struct ubifs_info {scalar_t__ max_sqnum; } ;
struct ubifs_dent_node {scalar_t__ type; int /*<<< orphan*/  nlen; int /*<<< orphan*/  key; int /*<<< orphan*/  inum; } ;
struct ubifs_data_node {int /*<<< orphan*/  size; int /*<<< orphan*/  key; } ;
struct ubifs_ch {int /*<<< orphan*/  sqnum; } ;
struct fsck_inode {long long size; int references; int calc_xcnt; int calc_xnms; int calc_cnt; int /*<<< orphan*/  calc_sz; int /*<<< orphan*/  calc_xsz; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ CALC_DENT_SIZE (int) ; 
 scalar_t__ CALC_XATTR_BYTES (long long) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct fsck_inode*) ; 
 int PTR_ERR (struct fsck_inode*) ; 
 long long UBIFS_BLOCK_SHIFT ; 
 scalar_t__ UBIFS_CH_SZ ; 
 int UBIFS_DATA_KEY ; 
 scalar_t__ UBIFS_DATA_NODE_SZ ; 
 int UBIFS_DENT_KEY ; 
 scalar_t__ UBIFS_DENT_NODE_SZ ; 
 int UBIFS_INO_KEY ; 
 scalar_t__ UBIFS_ITYPE_DIR ; 
 int UBIFS_XENT_KEY ; 
 struct fsck_inode* add_inode (struct ubifs_info*,void*,void*) ; 
 long long key_block_flash (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ key_inum_flash (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int key_type (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct fsck_inode* read_add_inode (struct ubifs_info*,void*,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,...) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_tnc_read_node (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 
 int ubifs_validate_entry (struct ubifs_info*,struct ubifs_dent_node*) ; 

__attribute__((used)) static int check_leaf(struct ubifs_info *c, struct ubifs_zbranch *zbr,
		      void *priv)
{
	ino_t inum;
	void *node;
	struct ubifs_ch *ch;
	int err, type = key_type(c, &zbr->key);
	struct fsck_inode *fscki;

	if (zbr->len < UBIFS_CH_SZ) {
		ubifs_err(c, "bad leaf length %d (LEB %d:%d)",
			  zbr->len, zbr->lnum, zbr->offs);
		return -EINVAL;
	}

	node = kmalloc(zbr->len, GFP_NOFS);
	if (!node)
		return -ENOMEM;

	err = ubifs_tnc_read_node(c, zbr, node);
	if (err) {
		ubifs_err(c, "cannot read leaf node at LEB %d:%d, error %d",
			  zbr->lnum, zbr->offs, err);
		goto out_free;
	}

	/* If this is an inode node, add it to RB-tree of inodes */
	if (type == UBIFS_INO_KEY) {
		fscki = add_inode(c, priv, node);
		if (IS_ERR(fscki)) {
			err = PTR_ERR(fscki);
			ubifs_err(c, "error %d while adding inode node", err);
			goto out_dump;
		}
		goto out;
	}

	if (type != UBIFS_DENT_KEY && type != UBIFS_XENT_KEY &&
	    type != UBIFS_DATA_KEY) {
		ubifs_err(c, "unexpected node type %d at LEB %d:%d",
			  type, zbr->lnum, zbr->offs);
		err = -EINVAL;
		goto out_free;
	}

	ch = node;
	if (le64_to_cpu(ch->sqnum) > c->max_sqnum) {
		ubifs_err(c, "too high sequence number, max. is %llu",
			  c->max_sqnum);
		err = -EINVAL;
		goto out_dump;
	}

	if (type == UBIFS_DATA_KEY) {
		long long blk_offs;
		struct ubifs_data_node *dn = node;

		ubifs_assert(c, zbr->len >= UBIFS_DATA_NODE_SZ);

		/*
		 * Search the inode node this data node belongs to and insert
		 * it to the RB-tree of inodes.
		 */
		inum = key_inum_flash(c, &dn->key);
		fscki = read_add_inode(c, priv, inum);
		if (IS_ERR(fscki)) {
			err = PTR_ERR(fscki);
			ubifs_err(c, "error %d while processing data node and trying to find inode node %lu",
				  err, (unsigned long)inum);
			goto out_dump;
		}

		/* Make sure the data node is within inode size */
		blk_offs = key_block_flash(c, &dn->key);
		blk_offs <<= UBIFS_BLOCK_SHIFT;
		blk_offs += le32_to_cpu(dn->size);
		if (blk_offs > fscki->size) {
			ubifs_err(c, "data node at LEB %d:%d is not within inode size %lld",
				  zbr->lnum, zbr->offs, fscki->size);
			err = -EINVAL;
			goto out_dump;
		}
	} else {
		int nlen;
		struct ubifs_dent_node *dent = node;
		struct fsck_inode *fscki1;

		ubifs_assert(c, zbr->len >= UBIFS_DENT_NODE_SZ);

		err = ubifs_validate_entry(c, dent);
		if (err)
			goto out_dump;

		/*
		 * Search the inode node this entry refers to and the parent
		 * inode node and insert them to the RB-tree of inodes.
		 */
		inum = le64_to_cpu(dent->inum);
		fscki = read_add_inode(c, priv, inum);
		if (IS_ERR(fscki)) {
			err = PTR_ERR(fscki);
			ubifs_err(c, "error %d while processing entry node and trying to find inode node %lu",
				  err, (unsigned long)inum);
			goto out_dump;
		}

		/* Count how many direntries or xentries refers this inode */
		fscki->references += 1;

		inum = key_inum_flash(c, &dent->key);
		fscki1 = read_add_inode(c, priv, inum);
		if (IS_ERR(fscki1)) {
			err = PTR_ERR(fscki1);
			ubifs_err(c, "error %d while processing entry node and trying to find parent inode node %lu",
				  err, (unsigned long)inum);
			goto out_dump;
		}

		nlen = le16_to_cpu(dent->nlen);
		if (type == UBIFS_XENT_KEY) {
			fscki1->calc_xcnt += 1;
			fscki1->calc_xsz += CALC_DENT_SIZE(nlen);
			fscki1->calc_xsz += CALC_XATTR_BYTES(fscki->size);
			fscki1->calc_xnms += nlen;
		} else {
			fscki1->calc_sz += CALC_DENT_SIZE(nlen);
			if (dent->type == UBIFS_ITYPE_DIR)
				fscki1->calc_cnt += 1;
		}
	}

out:
	kfree(node);
	return 0;

out_dump:
	ubifs_msg(c, "dump of node at LEB %d:%d", zbr->lnum, zbr->offs);
	ubifs_dump_node(c, node);
out_free:
	kfree(node);
	return err;
}