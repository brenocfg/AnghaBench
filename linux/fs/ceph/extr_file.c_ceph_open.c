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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; int f_mode; struct ceph_file_info* private_data; } ;
struct ceph_mds_request {int r_num_caps; int r_fmode; struct inode* r_inode; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_inode_info {int i_snap_caps; int /*<<< orphan*/  i_ceph_lock; scalar_t__ i_auth_cap; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;
struct ceph_file_info {int dummy; } ;

/* Variables and functions */
 int CEPH_FILE_MODE_WR ; 
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_EXCL ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __ceph_caps_issued (struct ceph_inode_info*,int /*<<< orphan*/ *) ; 
 int __ceph_caps_mds_wanted (struct ceph_inode_info*,int) ; 
 int /*<<< orphan*/  __ceph_get_fmode (struct ceph_inode_info*,int) ; 
 scalar_t__ __ceph_is_any_real_caps (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  ceph_cap_string (int) ; 
 int ceph_caps_for_mode (int) ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ceph_flags_to_mode (int) ; 
 int ceph_init_file (struct inode*,struct file*,int) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 struct ceph_mds_request* prepare_open_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_open(struct inode *inode, struct file *file)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_sb_to_client(inode->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	struct ceph_file_info *fi = file->private_data;
	int err;
	int flags, fmode, wanted;

	if (fi) {
		dout("open file %p is already opened\n", file);
		return 0;
	}

	/* filter out O_CREAT|O_EXCL; vfs did that already.  yuck. */
	flags = file->f_flags & ~(O_CREAT|O_EXCL);
	if (S_ISDIR(inode->i_mode))
		flags = O_DIRECTORY;  /* mds likes to know */

	dout("open inode %p ino %llx.%llx file %p flags %d (%d)\n", inode,
	     ceph_vinop(inode), file, flags, file->f_flags);
	fmode = ceph_flags_to_mode(flags);
	wanted = ceph_caps_for_mode(fmode);

	/* snapped files are read-only */
	if (ceph_snap(inode) != CEPH_NOSNAP && (file->f_mode & FMODE_WRITE))
		return -EROFS;

	/* trivially open snapdir */
	if (ceph_snap(inode) == CEPH_SNAPDIR) {
		spin_lock(&ci->i_ceph_lock);
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);
		return ceph_init_file(inode, file, fmode);
	}

	/*
	 * No need to block if we have caps on the auth MDS (for
	 * write) or any MDS (for read).  Update wanted set
	 * asynchronously.
	 */
	spin_lock(&ci->i_ceph_lock);
	if (__ceph_is_any_real_caps(ci) &&
	    (((fmode & CEPH_FILE_MODE_WR) == 0) || ci->i_auth_cap)) {
		int mds_wanted = __ceph_caps_mds_wanted(ci, true);
		int issued = __ceph_caps_issued(ci, NULL);

		dout("open %p fmode %d want %s issued %s using existing\n",
		     inode, fmode, ceph_cap_string(wanted),
		     ceph_cap_string(issued));
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);

		/* adjust wanted? */
		if ((issued & wanted) != wanted &&
		    (mds_wanted & wanted) != wanted &&
		    ceph_snap(inode) != CEPH_SNAPDIR)
			ceph_check_caps(ci, 0, NULL);

		return ceph_init_file(inode, file, fmode);
	} else if (ceph_snap(inode) != CEPH_NOSNAP &&
		   (ci->i_snap_caps & wanted) == wanted) {
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);
		return ceph_init_file(inode, file, fmode);
	}

	spin_unlock(&ci->i_ceph_lock);

	dout("open fmode %d wants %s\n", fmode, ceph_cap_string(wanted));
	req = prepare_open_request(inode->i_sb, flags, 0);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}
	req->r_inode = inode;
	ihold(inode);

	req->r_num_caps = 1;
	err = ceph_mdsc_do_request(mdsc, NULL, req);
	if (!err)
		err = ceph_init_file(inode, file, req->r_fmode);
	ceph_mdsc_put_request(req);
	dout("open result=%d on %llx.%llx\n", err, ceph_vinop(inode));
out:
	return err;
}