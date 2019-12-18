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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct qstr {int hash; char* name; int len; } ;
struct inode {int dummy; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_depth; int /*<<< orphan*/  lf_entries; } ;
struct gfs2_inode {int i_depth; struct inode i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_type; int /*<<< orphan*/  de_inum; int /*<<< orphan*/  de_hash; int /*<<< orphan*/  de_name_len; } ;
struct buffer_head {char* b_data; int /*<<< orphan*/  b_blocknr; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirent_del (struct gfs2_inode*,struct buffer_head*,struct gfs2_dirent*,struct gfs2_dirent*) ; 
 scalar_t__ dirent_next (struct gfs2_inode*,struct buffer_head*,struct gfs2_dirent**) ; 
 int /*<<< orphan*/  fs_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int get_leaf (struct gfs2_inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int get_leaf_nr (struct gfs2_inode*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (struct inode*,int) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,char*) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 int gfs2_dir_write_data (struct gfs2_inode*,char*,int,int) ; 
 int /*<<< orphan*/  gfs2_dirent_sentinel (struct gfs2_dirent*) ; 
 struct gfs2_dirent* gfs2_dirent_split_alloc (struct inode*,struct buffer_head*,struct qstr*,void*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct gfs2_leaf* new_leaf (struct inode*,struct buffer_head**,int) ; 

__attribute__((used)) static int dir_split_leaf(struct inode *inode, const struct qstr *name)
{
	struct gfs2_inode *dip = GFS2_I(inode);
	struct buffer_head *nbh, *obh, *dibh;
	struct gfs2_leaf *nleaf, *oleaf;
	struct gfs2_dirent *dent = NULL, *prev = NULL, *next = NULL, *new;
	u32 start, len, half_len, divider;
	u64 bn, leaf_no;
	__be64 *lp;
	u32 index;
	int x;
	int error;

	index = name->hash >> (32 - dip->i_depth);
	error = get_leaf_nr(dip, index, &leaf_no);
	if (error)
		return error;

	/*  Get the old leaf block  */
	error = get_leaf(dip, leaf_no, &obh);
	if (error)
		return error;

	oleaf = (struct gfs2_leaf *)obh->b_data;
	if (dip->i_depth == be16_to_cpu(oleaf->lf_depth)) {
		brelse(obh);
		return 1; /* can't split */
	}

	gfs2_trans_add_meta(dip->i_gl, obh);

	nleaf = new_leaf(inode, &nbh, be16_to_cpu(oleaf->lf_depth) + 1);
	if (!nleaf) {
		brelse(obh);
		return -ENOSPC;
	}
	bn = nbh->b_blocknr;

	/*  Compute the start and len of leaf pointers in the hash table.  */
	len = BIT(dip->i_depth - be16_to_cpu(oleaf->lf_depth));
	half_len = len >> 1;
	if (!half_len) {
		fs_warn(GFS2_SB(inode), "i_depth %u lf_depth %u index %u\n",
			dip->i_depth, be16_to_cpu(oleaf->lf_depth), index);
		gfs2_consist_inode(dip);
		error = -EIO;
		goto fail_brelse;
	}

	start = (index & ~(len - 1));

	/* Change the pointers.
	   Don't bother distinguishing stuffed from non-stuffed.
	   This code is complicated enough already. */
	lp = kmalloc_array(half_len, sizeof(__be64), GFP_NOFS);
	if (!lp) {
		error = -ENOMEM;
		goto fail_brelse;
	}

	/*  Change the pointers  */
	for (x = 0; x < half_len; x++)
		lp[x] = cpu_to_be64(bn);

	gfs2_dir_hash_inval(dip);

	error = gfs2_dir_write_data(dip, (char *)lp, start * sizeof(u64),
				    half_len * sizeof(u64));
	if (error != half_len * sizeof(u64)) {
		if (error >= 0)
			error = -EIO;
		goto fail_lpfree;
	}

	kfree(lp);

	/*  Compute the divider  */
	divider = (start + half_len) << (32 - dip->i_depth);

	/*  Copy the entries  */
	dent = (struct gfs2_dirent *)(obh->b_data + sizeof(struct gfs2_leaf));

	do {
		next = dent;
		if (dirent_next(dip, obh, &next))
			next = NULL;

		if (!gfs2_dirent_sentinel(dent) &&
		    be32_to_cpu(dent->de_hash) < divider) {
			struct qstr str;
			void *ptr = ((char *)dent - obh->b_data) + nbh->b_data;
			str.name = (char*)(dent+1);
			str.len = be16_to_cpu(dent->de_name_len);
			str.hash = be32_to_cpu(dent->de_hash);
			new = gfs2_dirent_split_alloc(inode, nbh, &str, ptr);
			if (IS_ERR(new)) {
				error = PTR_ERR(new);
				break;
			}

			new->de_inum = dent->de_inum; /* No endian worries */
			new->de_type = dent->de_type; /* No endian worries */
			be16_add_cpu(&nleaf->lf_entries, 1);

			dirent_del(dip, obh, prev, dent);

			if (!oleaf->lf_entries)
				gfs2_consist_inode(dip);
			be16_add_cpu(&oleaf->lf_entries, -1);

			if (!prev)
				prev = dent;
		} else {
			prev = dent;
		}
		dent = next;
	} while (dent);

	oleaf->lf_depth = nleaf->lf_depth;

	error = gfs2_meta_inode_buffer(dip, &dibh);
	if (!gfs2_assert_withdraw(GFS2_SB(&dip->i_inode), !error)) {
		gfs2_trans_add_meta(dip->i_gl, dibh);
		gfs2_add_inode_blocks(&dip->i_inode, 1);
		gfs2_dinode_out(dip, dibh->b_data);
		brelse(dibh);
	}

	brelse(obh);
	brelse(nbh);

	return error;

fail_lpfree:
	kfree(lp);

fail_brelse:
	brelse(obh);
	brelse(nbh);
	return error;
}