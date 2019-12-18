#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; } ;
struct TYPE_4__ {scalar_t__ data_version; } ;
struct afs_vnode {int /*<<< orphan*/  fid; int /*<<< orphan*/  flags; struct key* silly_key; TYPE_1__ status; } ;
struct afs_status_cb {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; } ;
typedef  scalar_t__ afs_dataversion_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_DIR_VALID ; 
 int /*<<< orphan*/  DCACHE_NFSFS_RENAMED ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_edit_dir_add (struct afs_vnode*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_edit_dir_for_silly_0 ; 
 int /*<<< orphan*/  afs_edit_dir_for_silly_1 ; 
 int /*<<< orphan*/  afs_edit_dir_remove (struct afs_vnode*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_fs_rename (struct afs_fs_cursor*,int /*<<< orphan*/ ,struct afs_vnode*,int /*<<< orphan*/ ,struct afs_status_cb*,struct afs_status_cb*) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,scalar_t__*,struct afs_status_cb*) ; 
 struct key* key_get (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 struct afs_status_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_silly_rename (struct afs_vnode*,int) ; 

__attribute__((used)) static int afs_do_silly_rename(struct afs_vnode *dvnode, struct afs_vnode *vnode,
			       struct dentry *old, struct dentry *new,
			       struct key *key)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	int ret = -ERESTARTSYS;

	_enter("%pd,%pd", old, new);

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_KERNEL);
	if (!scb)
		return -ENOMEM;

	trace_afs_silly_rename(vnode, false);
	if (afs_begin_vnode_operation(&fc, dvnode, key, true)) {
		afs_dataversion_t dir_data_version = dvnode->status.data_version + 1;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(dvnode);
			afs_fs_rename(&fc, old->d_name.name,
				      dvnode, new->d_name.name,
				      scb, scb);
		}

		afs_vnode_commit_status(&fc, dvnode, fc.cb_break,
					&dir_data_version, scb);
		ret = afs_end_vnode_operation(&fc);
	}

	if (ret == 0) {
		spin_lock(&old->d_lock);
		old->d_flags |= DCACHE_NFSFS_RENAMED;
		spin_unlock(&old->d_lock);
		if (dvnode->silly_key != key) {
			key_put(dvnode->silly_key);
			dvnode->silly_key = key_get(key);
		}

		if (test_bit(AFS_VNODE_DIR_VALID, &dvnode->flags))
			afs_edit_dir_remove(dvnode, &old->d_name,
					    afs_edit_dir_for_silly_0);
		if (test_bit(AFS_VNODE_DIR_VALID, &dvnode->flags))
			afs_edit_dir_add(dvnode, &new->d_name,
					 &vnode->fid, afs_edit_dir_for_silly_1);
	}

	kfree(scb);
	_leave(" = %d", ret);
	return ret;
}