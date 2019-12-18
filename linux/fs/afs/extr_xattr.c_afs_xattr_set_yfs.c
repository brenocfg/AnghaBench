#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xattr_handler {int dummy; } ;
struct key {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_version; } ;
struct afs_vnode {TYPE_2__ status; TYPE_1__* volume; } ;
struct afs_status_cb {size_t size; int /*<<< orphan*/  data; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; int /*<<< orphan*/  vnode; } ;
struct afs_acl {size_t size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
struct TYPE_3__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int XATTR_CREATE ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,int /*<<< orphan*/ ) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 struct afs_status_cb* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct afs_status_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  yfs_fs_store_opaque_acl2 (struct afs_fs_cursor*,struct afs_status_cb*,struct afs_status_cb*) ; 

__attribute__((used)) static int afs_xattr_set_yfs(const struct xattr_handler *handler,
                             struct dentry *dentry,
                             struct inode *inode, const char *name,
                             const void *buffer, size_t size, int flags)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	struct afs_vnode *vnode = AFS_FS_I(inode);
	struct afs_acl *acl = NULL;
	struct key *key;
	int ret = -ENOMEM;

	if (flags == XATTR_CREATE ||
	    strcmp(name, "acl") != 0)
		return -EINVAL;

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_NOFS);
	if (!scb)
		goto error;

	acl = kmalloc(sizeof(*acl) + size, GFP_KERNEL);
	if (!acl)
		goto error_scb;

	acl->size = size;
	memcpy(acl->data, buffer, size);

	key = afs_request_key(vnode->volume->cell);
	if (IS_ERR(key)) {
		ret = PTR_ERR(key);
		goto error_acl;
	}

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key, true)) {
		afs_dataversion_t data_version = vnode->status.data_version;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			yfs_fs_store_opaque_acl2(&fc, acl, scb);
		}

		afs_check_for_remote_deletion(&fc, fc.vnode);
		afs_vnode_commit_status(&fc, vnode, fc.cb_break,
					&data_version, scb);
		ret = afs_end_vnode_operation(&fc);
	}

error_acl:
	kfree(acl);
	key_put(key);
error_scb:
	kfree(scb);
error:
	return ret;
}