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
struct qstr {int hash; } ;
struct inode {int dummy; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_next; int /*<<< orphan*/  lf_dist; int /*<<< orphan*/  lf_depth; } ;
struct gfs2_inode {int i_depth; int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int get_first_leaf (struct gfs2_inode*,int,struct buffer_head**) ; 
 int get_leaf (struct gfs2_inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,scalar_t__) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct gfs2_leaf* new_leaf (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dir_new_leaf(struct inode *inode, const struct qstr *name)
{
	struct buffer_head *bh, *obh;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_leaf *leaf, *oleaf;
	u32 dist = 1;
	int error;
	u32 index;
	u64 bn;

	index = name->hash >> (32 - ip->i_depth);
	error = get_first_leaf(ip, index, &obh);
	if (error)
		return error;
	do {
		dist++;
		oleaf = (struct gfs2_leaf *)obh->b_data;
		bn = be64_to_cpu(oleaf->lf_next);
		if (!bn)
			break;
		brelse(obh);
		error = get_leaf(ip, bn, &obh);
		if (error)
			return error;
	} while(1);

	gfs2_trans_add_meta(ip->i_gl, obh);

	leaf = new_leaf(inode, &bh, be16_to_cpu(oleaf->lf_depth));
	if (!leaf) {
		brelse(obh);
		return -ENOSPC;
	}
	leaf->lf_dist = cpu_to_be32(dist);
	oleaf->lf_next = cpu_to_be64(bh->b_blocknr);
	brelse(bh);
	brelse(obh);

	error = gfs2_meta_inode_buffer(ip, &bh);
	if (error)
		return error;
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_add_inode_blocks(&ip->i_inode, 1);
	gfs2_dinode_out(ip, bh->b_data);
	brelse(bh);
	return 0;
}