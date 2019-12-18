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
struct key {int dummy; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_file; } ;
struct dentry {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_4__ status; TYPE_3__* volume; TYPE_2__ vfs_inode; TYPE_1__ fid; } ;
struct afs_status_cb {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
struct TYPE_7__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int ATTR_FILE ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,struct afs_vnode*) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 struct key* afs_file_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_fs_setattr (struct afs_fs_cursor*,struct iattr*,struct afs_status_cb*) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 struct afs_status_cb* kzalloc (int,int /*<<< orphan*/ ) ; 

int afs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	struct afs_vnode *vnode = AFS_FS_I(d_inode(dentry));
	struct key *key;
	int ret = -ENOMEM;

	_enter("{%llx:%llu},{n=%pd},%x",
	       vnode->fid.vid, vnode->fid.vnode, dentry,
	       attr->ia_valid);

	if (!(attr->ia_valid & (ATTR_SIZE | ATTR_MODE | ATTR_UID | ATTR_GID |
				ATTR_MTIME))) {
		_leave(" = 0 [unsupported]");
		return 0;
	}

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_KERNEL);
	if (!scb)
		goto error;

	/* flush any dirty data outstanding on a regular file */
	if (S_ISREG(vnode->vfs_inode.i_mode))
		filemap_write_and_wait(vnode->vfs_inode.i_mapping);

	if (attr->ia_valid & ATTR_FILE) {
		key = afs_file_key(attr->ia_file);
	} else {
		key = afs_request_key(vnode->volume->cell);
		if (IS_ERR(key)) {
			ret = PTR_ERR(key);
			goto error_scb;
		}
	}

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key, false)) {
		afs_dataversion_t data_version = vnode->status.data_version;

		if (attr->ia_valid & ATTR_SIZE)
			data_version++;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			afs_fs_setattr(&fc, attr, scb);
		}

		afs_check_for_remote_deletion(&fc, vnode);
		afs_vnode_commit_status(&fc, vnode, fc.cb_break,
					&data_version, scb);
		ret = afs_end_vnode_operation(&fc);
	}

	if (!(attr->ia_valid & ATTR_FILE))
		key_put(key);

error_scb:
	kfree(scb);
error:
	_leave(" = %d", ret);
	return ret;
}