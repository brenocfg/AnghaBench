#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_root; } ;
struct inode {scalar_t__ i_nlink; } ;
struct dentry {int dummy; } ;
struct ceph_vino {scalar_t__ ino; scalar_t__ snap; } ;
struct ceph_nfs_snapfh {scalar_t__ parent_ino; scalar_t__ snapid; scalar_t__ ino; int hash; } ;
struct TYPE_4__ {void* hash; void* parent; void* snapid; void* mask; } ;
struct TYPE_5__ {TYPE_1__ lookupino; } ;
struct ceph_mds_request {int r_num_caps; struct inode* r_target_inode; struct ceph_vino r_ino1; TYPE_2__ r_args; } ;
struct ceph_mds_client {int dummy; } ;
struct TYPE_6__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int CEPH_CAP_XATTR_SHARED ; 
 int /*<<< orphan*/  CEPH_MDS_OP_LOOKUPINO ; 
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int CEPH_STAT_CAP_INODE ; 
 int EOPNOTSUPP ; 
 struct dentry* ERR_CAST (struct ceph_mds_request*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_ANY_MDS ; 
 struct inode* ceph_find_inode (struct super_block*,struct ceph_vino) ; 
 struct inode* ceph_get_snapdir (struct inode*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 TYPE_3__* ceph_sb_to_client (struct super_block*) ; 
 scalar_t__ ceph_security_xattr_wanted (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct dentry* d_obtain_root (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 

__attribute__((used)) static struct dentry *__snapfh_to_dentry(struct super_block *sb,
					  struct ceph_nfs_snapfh *sfh,
					  bool want_parent)
{
	struct ceph_mds_client *mdsc = ceph_sb_to_client(sb)->mdsc;
	struct ceph_mds_request *req;
	struct inode *inode;
	struct ceph_vino vino;
	int mask;
	int err;
	bool unlinked = false;

	if (want_parent) {
		vino.ino = sfh->parent_ino;
		if (sfh->snapid == CEPH_SNAPDIR)
			vino.snap = CEPH_NOSNAP;
		else if (sfh->ino == sfh->parent_ino)
			vino.snap = CEPH_SNAPDIR;
		else
			vino.snap = sfh->snapid;
	} else {
		vino.ino = sfh->ino;
		vino.snap = sfh->snapid;
	}
	inode = ceph_find_inode(sb, vino);
	if (inode)
		return d_obtain_alias(inode);

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPINO,
				       USE_ANY_MDS);
	if (IS_ERR(req))
		return ERR_CAST(req);

	mask = CEPH_STAT_CAP_INODE;
	if (ceph_security_xattr_wanted(d_inode(sb->s_root)))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.lookupino.mask = cpu_to_le32(mask);
	if (vino.snap < CEPH_NOSNAP) {
		req->r_args.lookupino.snapid = cpu_to_le64(vino.snap);
		if (!want_parent && sfh->ino != sfh->parent_ino) {
			req->r_args.lookupino.parent =
					cpu_to_le64(sfh->parent_ino);
			req->r_args.lookupino.hash =
					cpu_to_le32(sfh->hash);
		}
	}

	req->r_ino1 = vino;
	req->r_num_caps = 1;
	err = ceph_mdsc_do_request(mdsc, NULL, req);
	inode = req->r_target_inode;
	if (inode) {
		if (vino.snap == CEPH_SNAPDIR) {
			if (inode->i_nlink == 0)
				unlinked = true;
			inode = ceph_get_snapdir(inode);
		} else if (ceph_snap(inode) == vino.snap) {
			ihold(inode);
		} else {
			/* mds does not support lookup snapped inode */
			err = -EOPNOTSUPP;
			inode = NULL;
		}
	}
	ceph_mdsc_put_request(req);

	if (want_parent) {
		dout("snapfh_to_parent %llx.%llx\n err=%d\n",
		     vino.ino, vino.snap, err);
	} else {
		dout("snapfh_to_dentry %llx.%llx parent %llx hash %x err=%d",
		      vino.ino, vino.snap, sfh->parent_ino, sfh->hash, err);
	}
	if (!inode)
		return ERR_PTR(-ESTALE);
	/* see comments in ceph_get_parent() */
	return unlinked ? d_obtain_root(inode) : d_obtain_alias(inode);
}