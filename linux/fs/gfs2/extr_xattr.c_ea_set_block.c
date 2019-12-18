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
struct gfs2_sbd {int sd_inptrs; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_eattr; int /*<<< orphan*/  i_gl; } ;
struct gfs2_ea_request {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_WAIT ; 
 int EIO ; 
 int ENOSPC ; 
 int GFS2_DIF_EA_INDIRECT ; 
 int /*<<< orphan*/  GFS2_EA_BH2FIRST (struct buffer_head*) ; 
 int /*<<< orphan*/  GFS2_FORMAT_IN ; 
 int /*<<< orphan*/  GFS2_METATYPE_IN ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int ea_alloc_blk (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ea_set_remove_stuffed (struct gfs2_inode*,void*) ; 
 int ea_write (struct gfs2_inode*,int /*<<< orphan*/ ,struct gfs2_ea_request*) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (int /*<<< orphan*/ *,int) ; 
 int gfs2_alloc_blocks (struct gfs2_inode*,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 struct buffer_head* gfs2_meta_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_metatype_set (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_trans_remove_revoke (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ea_set_block(struct gfs2_inode *ip, struct gfs2_ea_request *er,
			void *private)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *indbh, *newbh;
	__be64 *eablk;
	int error;
	int mh_size = sizeof(struct gfs2_meta_header);

	if (ip->i_diskflags & GFS2_DIF_EA_INDIRECT) {
		__be64 *end;

		error = gfs2_meta_read(ip->i_gl, ip->i_eattr, DIO_WAIT, 0,
				       &indbh);
		if (error)
			return error;

		if (gfs2_metatype_check(sdp, indbh, GFS2_METATYPE_IN)) {
			error = -EIO;
			goto out;
		}

		eablk = (__be64 *)(indbh->b_data + mh_size);
		end = eablk + sdp->sd_inptrs;

		for (; eablk < end; eablk++)
			if (!*eablk)
				break;

		if (eablk == end) {
			error = -ENOSPC;
			goto out;
		}

		gfs2_trans_add_meta(ip->i_gl, indbh);
	} else {
		u64 blk;
		unsigned int n = 1;
		error = gfs2_alloc_blocks(ip, &blk, &n, 0, NULL);
		if (error)
			return error;
		gfs2_trans_remove_revoke(sdp, blk, 1);
		indbh = gfs2_meta_new(ip->i_gl, blk);
		gfs2_trans_add_meta(ip->i_gl, indbh);
		gfs2_metatype_set(indbh, GFS2_METATYPE_IN, GFS2_FORMAT_IN);
		gfs2_buffer_clear_tail(indbh, mh_size);

		eablk = (__be64 *)(indbh->b_data + mh_size);
		*eablk = cpu_to_be64(ip->i_eattr);
		ip->i_eattr = blk;
		ip->i_diskflags |= GFS2_DIF_EA_INDIRECT;
		gfs2_add_inode_blocks(&ip->i_inode, 1);

		eablk++;
	}

	error = ea_alloc_blk(ip, &newbh);
	if (error)
		goto out;

	*eablk = cpu_to_be64((u64)newbh->b_blocknr);
	error = ea_write(ip, GFS2_EA_BH2FIRST(newbh), er);
	brelse(newbh);
	if (error)
		goto out;

	if (private)
		ea_set_remove_stuffed(ip, private);

out:
	brelse(indbh);
	return error;
}