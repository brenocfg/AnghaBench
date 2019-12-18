#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
typedef  char const dentry ;
struct TYPE_9__ {int /*<<< orphan*/  mask; } ;
struct TYPE_10__ {TYPE_4__ getattr; } ;
struct TYPE_6__ {int /*<<< orphan*/  snap; int /*<<< orphan*/  ino; } ;
struct ceph_mds_request {unsigned long r_started; int r_num_caps; struct inode* r_target_inode; TYPE_5__ r_args; int /*<<< orphan*/  r_timeout; TYPE_1__ r_ino1; int /*<<< orphan*/  r_path1; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {TYPE_3__* client; struct ceph_mds_client* mdsc; } ;
struct TYPE_8__ {TYPE_2__* options; } ;
struct TYPE_7__ {int /*<<< orphan*/  mount_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_INO_ROOT ; 
 int /*<<< orphan*/  CEPH_MDS_OP_GETATTR ; 
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  CEPH_STAT_CAP_INODE ; 
 int ENOMEM ; 
 char const* ERR_CAST (struct ceph_mds_request*) ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_ANY_MDS ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 char* d_make_root (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *open_root_dentry(struct ceph_fs_client *fsc,
				       const char *path,
				       unsigned long started)
{
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req = NULL;
	int err;
	struct dentry *root;

	/* open dir */
	dout("open_root_inode opening '%s'\n", path);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_GETATTR, USE_ANY_MDS);
	if (IS_ERR(req))
		return ERR_CAST(req);
	req->r_path1 = kstrdup(path, GFP_NOFS);
	if (!req->r_path1) {
		root = ERR_PTR(-ENOMEM);
		goto out;
	}

	req->r_ino1.ino = CEPH_INO_ROOT;
	req->r_ino1.snap = CEPH_NOSNAP;
	req->r_started = started;
	req->r_timeout = fsc->client->options->mount_timeout;
	req->r_args.getattr.mask = cpu_to_le32(CEPH_STAT_CAP_INODE);
	req->r_num_caps = 2;
	err = ceph_mdsc_do_request(mdsc, NULL, req);
	if (err == 0) {
		struct inode *inode = req->r_target_inode;
		req->r_target_inode = NULL;
		dout("open_root_inode success\n");
		root = d_make_root(inode);
		if (!root) {
			root = ERR_PTR(-ENOMEM);
			goto out;
		}
		dout("open_root_inode success, root dentry is %p\n", root);
	} else {
		root = ERR_PTR(err);
	}
out:
	ceph_mdsc_put_request(req);
	return root;
}