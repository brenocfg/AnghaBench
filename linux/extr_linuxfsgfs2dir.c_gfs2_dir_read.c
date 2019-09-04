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
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int i_diskflags; scalar_t__ i_entries; scalar_t__ i_no_addr; } ;
struct gfs2_dirent {int dummy; } ;
struct file_ra_state {int dummy; } ;
struct dirent_gather {scalar_t__ offset; struct gfs2_dirent const** pdent; } ;
struct dir_context {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int GFS2_DIF_EXHASH ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int dir_e_read (struct inode*,struct dir_context*,struct file_ra_state*) ; 
 int do_filldir_main (struct gfs2_inode*,struct dir_context*,struct gfs2_dirent**,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned long long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dirent_gather ; 
 struct gfs2_dirent* gfs2_dirent_scan (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dirent_gather*) ; 
 int /*<<< orphan*/  gfs2_is_stuffed (struct gfs2_inode*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_set_cookies (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ,struct gfs2_dirent**,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gfs2_dirent**) ; 
 struct gfs2_dirent** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

int gfs2_dir_read(struct inode *inode, struct dir_context *ctx,
		  struct file_ra_state *f_ra)
{
	struct gfs2_inode *dip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct dirent_gather g;
	struct gfs2_dirent **darr, *dent;
	struct buffer_head *dibh;
	int copied = 0;
	int error;

	if (!dip->i_entries)
		return 0;

	if (dip->i_diskflags & GFS2_DIF_EXHASH)
		return dir_e_read(inode, ctx, f_ra);

	if (!gfs2_is_stuffed(dip)) {
		gfs2_consist_inode(dip);
		return -EIO;
	}

	error = gfs2_meta_inode_buffer(dip, &dibh);
	if (error)
		return error;

	error = -ENOMEM;
	/* 96 is max number of dirents which can be stuffed into an inode */
	darr = kmalloc_array(96, sizeof(struct gfs2_dirent *), GFP_NOFS);
	if (darr) {
		g.pdent = (const struct gfs2_dirent **)darr;
		g.offset = 0;
		dent = gfs2_dirent_scan(inode, dibh->b_data, dibh->b_size,
					gfs2_dirent_gather, NULL, &g);
		if (IS_ERR(dent)) {
			error = PTR_ERR(dent);
			goto out;
		}
		if (dip->i_entries != g.offset) {
			fs_warn(sdp, "Number of entries corrupt in dir %llu, "
				"ip->i_entries (%u) != g.offset (%u)\n",
				(unsigned long long)dip->i_no_addr,
				dip->i_entries,
				g.offset);
			gfs2_consist_inode(dip);
			error = -EIO;
			goto out;
		}
		gfs2_set_cookies(sdp, dibh, 0, darr, dip->i_entries);
		error = do_filldir_main(dip, ctx, darr,
					dip->i_entries, 0, &copied);
out:
		kfree(darr);
	}

	if (error > 0)
		error = 0;

	brelse(dibh);

	return error;
}