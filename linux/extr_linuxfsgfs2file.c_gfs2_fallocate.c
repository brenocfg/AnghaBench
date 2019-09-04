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
struct inode {scalar_t__ i_size; } ;
struct gfs2_sbd {struct inode* sd_rindex; } ;
struct gfs2_inode {int /*<<< orphan*/  i_res; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int __gfs2_fallocate (struct file*,int,scalar_t__,scalar_t__) ; 
 int __gfs2_punch_hole (struct file*,scalar_t__,scalar_t__) ; 
 struct inode* file_inode (struct file*) ; 
 int get_write_access (struct inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (int /*<<< orphan*/ *) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 

__attribute__((used)) static long gfs2_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
{
	struct inode *inode = file_inode(file);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	int ret;

	if (mode & ~(FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE))
		return -EOPNOTSUPP;
	/* fallocate is needed by gfs2_grow to reserve space in the rindex */
	if (gfs2_is_jdata(ip) && inode != sdp->sd_rindex)
		return -EOPNOTSUPP;

	inode_lock(inode);

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	if (ret)
		goto out_uninit;

	if (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    (offset + len) > inode->i_size) {
		ret = inode_newsize_ok(inode, offset + len);
		if (ret)
			goto out_unlock;
	}

	ret = get_write_access(inode);
	if (ret)
		goto out_unlock;

	if (mode & FALLOC_FL_PUNCH_HOLE) {
		ret = __gfs2_punch_hole(file, offset, len);
	} else {
		ret = gfs2_rsqa_alloc(ip);
		if (ret)
			goto out_putw;

		ret = __gfs2_fallocate(file, mode, offset, len);

		if (ret)
			gfs2_rs_deltree(&ip->i_res);
	}

out_putw:
	put_write_access(inode);
out_unlock:
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	inode_unlock(inode);
	return ret;
}