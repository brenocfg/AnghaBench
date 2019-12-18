#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct inode {TYPE_2__ d_name; int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_2__ d_name; int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; } ;
struct TYPE_8__ {TYPE_3__ getattr; } ;
struct ceph_mds_request {int r_num_caps; int /*<<< orphan*/  r_req_flags; struct inode* r_parent; TYPE_4__ r_args; int /*<<< orphan*/  r_dentry; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_shared_gen; int /*<<< orphan*/  i_ceph_flags; } ;
struct ceph_fs_client {TYPE_1__* mount_options; struct ceph_mds_client* mdsc; } ;
struct ceph_dentry_info {int /*<<< orphan*/  lease_shared_gen; } ;
struct TYPE_5__ {int /*<<< orphan*/  snapdir_name; } ;

/* Variables and functions */
 int CEPH_CAP_AUTH_SHARED ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_XATTR_SHARED ; 
 int CEPH_MDS_OP_LOOKUP ; 
 int CEPH_MDS_OP_LOOKUPSNAP ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int CEPH_STAT_CAP_INODE ; 
 int /*<<< orphan*/  DCACHE ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct inode* ERR_CAST (struct ceph_mds_request*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  USE_ANY_MDS ; 
 scalar_t__ __ceph_caps_issued_mask (struct ceph_inode_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __ceph_dir_is_complete (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct ceph_dentry_info* ceph_dentry (struct inode*) ; 
 struct inode* ceph_finish_lookup (struct ceph_mds_request*,struct inode*,int) ; 
 int ceph_handle_snapdir (struct ceph_mds_request*,struct inode*,int) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_security_xattr_wanted (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 scalar_t__ ceph_test_mount_opt (struct ceph_fs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  d_add (struct inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ d_really_is_negative (struct inode*) ; 
 int /*<<< orphan*/  dget (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,...) ; 
 int /*<<< orphan*/  is_root_ceph_dentry (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *ceph_lookup(struct inode *dir, struct dentry *dentry,
				  unsigned int flags)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	int op;
	int mask;
	int err;

	dout("lookup %p dentry %p '%pd'\n",
	     dir, dentry, dentry);

	if (dentry->d_name.len > NAME_MAX)
		return ERR_PTR(-ENAMETOOLONG);

	/* can we conclude ENOENT locally? */
	if (d_really_is_negative(dentry)) {
		struct ceph_inode_info *ci = ceph_inode(dir);
		struct ceph_dentry_info *di = ceph_dentry(dentry);

		spin_lock(&ci->i_ceph_lock);
		dout(" dir %p flags are %d\n", dir, ci->i_ceph_flags);
		if (strncmp(dentry->d_name.name,
			    fsc->mount_options->snapdir_name,
			    dentry->d_name.len) &&
		    !is_root_ceph_dentry(dir, dentry) &&
		    ceph_test_mount_opt(fsc, DCACHE) &&
		    __ceph_dir_is_complete(ci) &&
		    (__ceph_caps_issued_mask(ci, CEPH_CAP_FILE_SHARED, 1))) {
			spin_unlock(&ci->i_ceph_lock);
			dout(" dir %p complete, -ENOENT\n", dir);
			d_add(dentry, NULL);
			di->lease_shared_gen = atomic_read(&ci->i_shared_gen);
			return NULL;
		}
		spin_unlock(&ci->i_ceph_lock);
	}

	op = ceph_snap(dir) == CEPH_SNAPDIR ?
		CEPH_MDS_OP_LOOKUPSNAP : CEPH_MDS_OP_LOOKUP;
	req = ceph_mdsc_create_request(mdsc, op, USE_ANY_MDS);
	if (IS_ERR(req))
		return ERR_CAST(req);
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;

	mask = CEPH_STAT_CAP_INODE | CEPH_CAP_AUTH_SHARED;
	if (ceph_security_xattr_wanted(dir))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.getattr.mask = cpu_to_le32(mask);

	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	err = ceph_mdsc_do_request(mdsc, NULL, req);
	err = ceph_handle_snapdir(req, dentry, err);
	dentry = ceph_finish_lookup(req, dentry, err);
	ceph_mdsc_put_request(req);  /* will dput(dentry) */
	dout("lookup result=%p\n", dentry);
	return dentry;
}