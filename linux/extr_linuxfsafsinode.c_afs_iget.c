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
struct super_block {struct afs_super_info* s_fs_info; } ;
struct key {int dummy; } ;
struct inode {int i_state; int /*<<< orphan*/  i_flags; } ;
struct afs_vnode {scalar_t__ cb_type; scalar_t__ cb_version; int /*<<< orphan*/  flags; scalar_t__ cb_expires_at; int /*<<< orphan*/  cb_interest; int /*<<< orphan*/  status; } ;
struct afs_super_info {int /*<<< orphan*/  volume; } ;
struct afs_fid {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_iget_data {int /*<<< orphan*/  volume; struct afs_fid fid; } ;
struct afs_file_status {int dummy; } ;
struct afs_cb_interest {int dummy; } ;
struct afs_callback {scalar_t__ expiry; scalar_t__ type; scalar_t__ version; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_UNSET ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 int /*<<< orphan*/  S_NOATIME ; 
 int /*<<< orphan*/  _debug (char*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_fetch_status (struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_get_cb_interest (struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_get_inode_cache (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_iget5_set ; 
 int /*<<< orphan*/  afs_iget5_test ; 
 int afs_inode_init_from_status (struct afs_vnode*,struct key*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct afs_iget_data*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct afs_file_status*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *afs_iget(struct super_block *sb, struct key *key,
		       struct afs_fid *fid, struct afs_file_status *status,
		       struct afs_callback *cb, struct afs_cb_interest *cbi)
{
	struct afs_iget_data data = { .fid = *fid };
	struct afs_super_info *as;
	struct afs_vnode *vnode;
	struct inode *inode;
	int ret;

	_enter(",{%x:%u.%u},,", fid->vid, fid->vnode, fid->unique);

	as = sb->s_fs_info;
	data.volume = as->volume;

	inode = iget5_locked(sb, fid->vnode, afs_iget5_test, afs_iget5_set,
			     &data);
	if (!inode) {
		_leave(" = -ENOMEM");
		return ERR_PTR(-ENOMEM);
	}

	_debug("GOT INODE %p { vl=%x vn=%x, u=%x }",
	       inode, fid->vid, fid->vnode, fid->unique);

	vnode = AFS_FS_I(inode);

	/* deal with an existing inode */
	if (!(inode->i_state & I_NEW)) {
		_leave(" = %p", inode);
		return inode;
	}

	if (!status) {
		/* it's a remotely extant inode */
		ret = afs_fetch_status(vnode, key, true);
		if (ret < 0)
			goto bad_inode;
	} else {
		/* it's an inode we just created */
		memcpy(&vnode->status, status, sizeof(vnode->status));

		if (!cb) {
			/* it's a symlink we just created (the fileserver
			 * didn't give us a callback) */
			vnode->cb_version = 0;
			vnode->cb_type = 0;
			vnode->cb_expires_at = 0;
		} else {
			vnode->cb_version = cb->version;
			vnode->cb_type = cb->type;
			vnode->cb_expires_at = cb->expiry;
			vnode->cb_interest = afs_get_cb_interest(cbi);
			set_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
		}

		vnode->cb_expires_at += ktime_get_real_seconds();
	}

	ret = afs_inode_init_from_status(vnode, key);
	if (ret < 0)
		goto bad_inode;

	afs_get_inode_cache(vnode);

	/* success */
	clear_bit(AFS_VNODE_UNSET, &vnode->flags);
	inode->i_flags |= S_NOATIME;
	unlock_new_inode(inode);
	_leave(" = %p [CB { v=%u t=%u }]", inode, vnode->cb_version, vnode->cb_type);
	return inode;

	/* failure */
bad_inode:
	iget_failed(inode);
	_leave(" = %d [bad]", ret);
	return ERR_PTR(ret);
}