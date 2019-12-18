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
struct dentry {int dummy; } ;
struct ceph_mds_reply_info_parsed {int dir_nr; struct ceph_mds_reply_dir_entry* dir_entries; scalar_t__ dir_end; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_2__ readdir; } ;
struct ceph_mds_request {unsigned int r_readdir_offset; char* r_path2; struct ceph_mds_reply_info_parsed r_reply_info; int /*<<< orphan*/  r_dentry; struct inode* r_inode; TYPE_3__ r_args; int /*<<< orphan*/  r_direct_mode; } ;
struct TYPE_10__ {TYPE_4__* in; } ;
struct ceph_mds_reply_dir_entry {size_t name_len; int /*<<< orphan*/  name; TYPE_5__ inode; } ;
struct ceph_fs_client {int /*<<< orphan*/  mdsc; TYPE_1__* mount_options; } ;
struct TYPE_9__ {int /*<<< orphan*/  snapid; } ;
struct TYPE_6__ {int /*<<< orphan*/  snapdir_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_MDS_OP_LSSNAP ; 
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  CEPH_READDIR_REPLY_BITFLAGS ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 int ceph_alloc_readdir_reply_buffer (struct ceph_mds_request*,struct inode*) ; 
 scalar_t__ ceph_ino (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __get_snap_name(struct dentry *parent, char *name,
			   struct dentry *child)
{
	struct inode *inode = d_inode(child);
	struct inode *dir = d_inode(parent);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_mds_request *req = NULL;
	char *last_name = NULL;
	unsigned next_offset = 2;
	int err = -EINVAL;

	if (ceph_ino(inode) != ceph_ino(dir))
		goto out;
	if (ceph_snap(inode) == CEPH_SNAPDIR) {
		if (ceph_snap(dir) == CEPH_NOSNAP) {
			strcpy(name, fsc->mount_options->snapdir_name);
			err = 0;
		}
		goto out;
	}
	if (ceph_snap(dir) != CEPH_SNAPDIR)
		goto out;

	while (1) {
		struct ceph_mds_reply_info_parsed *rinfo;
		struct ceph_mds_reply_dir_entry *rde;
		int i;

		req = ceph_mdsc_create_request(fsc->mdsc, CEPH_MDS_OP_LSSNAP,
					       USE_AUTH_MDS);
		if (IS_ERR(req)) {
			err = PTR_ERR(req);
			req = NULL;
			goto out;
		}
		err = ceph_alloc_readdir_reply_buffer(req, inode);
		if (err)
			goto out;

		req->r_direct_mode = USE_AUTH_MDS;
		req->r_readdir_offset = next_offset;
		req->r_args.readdir.flags =
				cpu_to_le16(CEPH_READDIR_REPLY_BITFLAGS);
		if (last_name) {
			req->r_path2 = last_name;
			last_name = NULL;
		}

		req->r_inode = dir;
		ihold(dir);
		req->r_dentry = dget(parent);

		inode_lock(dir);
		err = ceph_mdsc_do_request(fsc->mdsc, NULL, req);
		inode_unlock(dir);

		if (err < 0)
			goto out;

		rinfo = &req->r_reply_info;
		for (i = 0; i < rinfo->dir_nr; i++) {
			rde = rinfo->dir_entries + i;
			BUG_ON(!rde->inode.in);
			if (ceph_snap(inode) ==
			    le64_to_cpu(rde->inode.in->snapid)) {
				memcpy(name, rde->name, rde->name_len);
				name[rde->name_len] = '\0';
				err = 0;
				goto out;
			}
		}

		if (rinfo->dir_end)
			break;

		BUG_ON(rinfo->dir_nr <= 0);
		rde = rinfo->dir_entries + (rinfo->dir_nr - 1);
		next_offset += rinfo->dir_nr;
		last_name = kstrndup(rde->name, rde->name_len, GFP_KERNEL);
		if (!last_name) {
			err = -ENOMEM;
			goto out;
		}

		ceph_mdsc_put_request(req);
		req = NULL;
	}
	err = -ENOENT;
out:
	if (req)
		ceph_mdsc_put_request(req);
	kfree(last_name);
	dout("get_snap_name %p ino %llx.%llx err=%d\n",
	     child, ceph_vinop(inode), err);
	return err;
}