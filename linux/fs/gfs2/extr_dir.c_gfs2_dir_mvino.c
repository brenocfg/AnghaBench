#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qstr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_type; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dirent_find ; 
 struct gfs2_dirent* gfs2_dirent_search (TYPE_1__*,struct qstr const*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_inum_out (struct gfs2_inode const*,struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (TYPE_1__*) ; 

int gfs2_dir_mvino(struct gfs2_inode *dip, const struct qstr *filename,
		   const struct gfs2_inode *nip, unsigned int new_type)
{
	struct buffer_head *bh;
	struct gfs2_dirent *dent;

	dent = gfs2_dirent_search(&dip->i_inode, filename, gfs2_dirent_find, &bh);
	if (!dent) {
		gfs2_consist_inode(dip);
		return -EIO;
	}
	if (IS_ERR(dent))
		return PTR_ERR(dent);

	gfs2_trans_add_meta(dip->i_gl, bh);
	gfs2_inum_out(nip, dent);
	dent->de_type = cpu_to_be16(new_type);
	brelse(bh);

	dip->i_inode.i_mtime = dip->i_inode.i_ctime = current_time(&dip->i_inode);
	mark_inode_dirty_sync(&dip->i_inode);
	return 0;
}