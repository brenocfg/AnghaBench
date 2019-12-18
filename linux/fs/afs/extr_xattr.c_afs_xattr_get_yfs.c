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
struct yfs_acl {int inherit_flag; int num_cleaned; TYPE_4__* vol_acl; TYPE_3__* acl; int /*<<< orphan*/  flags; } ;
struct xattr_handler {int dummy; } ;
struct key {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_version; } ;
struct afs_vnode {TYPE_2__ status; TYPE_1__* volume; } ;
struct afs_status_cb {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; int /*<<< orphan*/  vnode; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
struct TYPE_8__ {char* data; int size; } ;
struct TYPE_7__ {char* data; int size; } ;
struct TYPE_5__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  YFS_ACL_WANT_ACL ; 
 int /*<<< orphan*/  YFS_ACL_WANT_VOL_ACL ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,int /*<<< orphan*/ ) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  yfs_free_opaque_acl (struct yfs_acl*) ; 
 int /*<<< orphan*/  yfs_fs_fetch_opaque_acl (struct afs_fs_cursor*,struct yfs_acl*,struct afs_status_cb*) ; 

__attribute__((used)) static int afs_xattr_get_yfs(const struct xattr_handler *handler,
			     struct dentry *dentry,
			     struct inode *inode, const char *name,
			     void *buffer, size_t size)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	struct afs_vnode *vnode = AFS_FS_I(inode);
	struct yfs_acl *yacl = NULL;
	struct key *key;
	char buf[16], *data;
	int which = 0, dsize, ret = -ENOMEM;

	if (strcmp(name, "acl") == 0)
		which = 0;
	else if (strcmp(name, "acl_inherited") == 0)
		which = 1;
	else if (strcmp(name, "acl_num_cleaned") == 0)
		which = 2;
	else if (strcmp(name, "vol_acl") == 0)
		which = 3;
	else
		return -EOPNOTSUPP;

	yacl = kzalloc(sizeof(struct yfs_acl), GFP_KERNEL);
	if (!yacl)
		goto error;

	if (which == 0)
		yacl->flags |= YFS_ACL_WANT_ACL;
	else if (which == 3)
		yacl->flags |= YFS_ACL_WANT_VOL_ACL;

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_NOFS);
	if (!scb)
		goto error_yacl;

	key = afs_request_key(vnode->volume->cell);
	if (IS_ERR(key)) {
		ret = PTR_ERR(key);
		goto error_scb;
	}

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key, true)) {
		afs_dataversion_t data_version = vnode->status.data_version;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			yfs_fs_fetch_opaque_acl(&fc, yacl, scb);
		}

		afs_check_for_remote_deletion(&fc, fc.vnode);
		afs_vnode_commit_status(&fc, vnode, fc.cb_break,
					&data_version, scb);
		ret = afs_end_vnode_operation(&fc);
	}

	if (ret < 0)
		goto error_key;

	switch (which) {
	case 0:
		data = yacl->acl->data;
		dsize = yacl->acl->size;
		break;
	case 1:
		data = buf;
		dsize = snprintf(buf, sizeof(buf), "%u", yacl->inherit_flag);
		break;
	case 2:
		data = buf;
		dsize = snprintf(buf, sizeof(buf), "%u", yacl->num_cleaned);
		break;
	case 3:
		data = yacl->vol_acl->data;
		dsize = yacl->vol_acl->size;
		break;
	default:
		ret = -EOPNOTSUPP;
		goto error_key;
	}

	ret = dsize;
	if (size > 0) {
		if (dsize > size) {
			ret = -ERANGE;
			goto error_key;
		}
		memcpy(buffer, data, dsize);
	}

error_key:
	key_put(key);
error_scb:
	kfree(scb);
error_yacl:
	yfs_free_opaque_acl(yacl);
error:
	return ret;
}