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
struct qstr {int hash; } ;
struct inode {int dummy; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_next; } ;
struct gfs2_inode {int i_diskflags; int i_depth; } ;
struct gfs2_dirent {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  gfs2_dscan_t ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EIO ; 
 struct gfs2_dirent* ERR_PTR (int) ; 
 int GFS2_DIF_EXHASH ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int get_first_leaf (struct gfs2_inode*,unsigned int,struct buffer_head**) ; 
 int get_leaf (struct gfs2_inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 struct gfs2_dirent* gfs2_dirent_scan (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*,int /*<<< orphan*/ *) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 unsigned int i_size_read (struct inode*) ; 

__attribute__((used)) static struct gfs2_dirent *gfs2_dirent_search(struct inode *inode,
					      const struct qstr *name,
					      gfs2_dscan_t scan,
					      struct buffer_head **pbh)
{
	struct buffer_head *bh;
	struct gfs2_dirent *dent;
	struct gfs2_inode *ip = GFS2_I(inode);
	int error;

	if (ip->i_diskflags & GFS2_DIF_EXHASH) {
		struct gfs2_leaf *leaf;
		unsigned int hsize = BIT(ip->i_depth);
		unsigned int index;
		u64 ln;
		if (hsize * sizeof(u64) != i_size_read(inode)) {
			gfs2_consist_inode(ip);
			return ERR_PTR(-EIO);
		}

		index = name->hash >> (32 - ip->i_depth);
		error = get_first_leaf(ip, index, &bh);
		if (error)
			return ERR_PTR(error);
		do {
			dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
						scan, name, NULL);
			if (dent)
				goto got_dent;
			leaf = (struct gfs2_leaf *)bh->b_data;
			ln = be64_to_cpu(leaf->lf_next);
			brelse(bh);
			if (!ln)
				break;

			error = get_leaf(ip, ln, &bh);
		} while(!error);

		return error ? ERR_PTR(error) : NULL;
	}


	error = gfs2_meta_inode_buffer(ip, &bh);
	if (error)
		return ERR_PTR(error);
	dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size, scan, name, NULL);
got_dent:
	if (IS_ERR_OR_NULL(dent)) {
		brelse(bh);
		bh = NULL;
	}
	*pbh = bh;
	return dent;
}