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
struct TYPE_7__ {int /*<<< orphan*/  data_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_3__ status; int /*<<< orphan*/  flags; TYPE_2__ fid; TYPE_1__* volume; } ;
struct TYPE_8__ {int /*<<< orphan*/  caller_access; } ;
struct afs_status_cb {TYPE_4__ status; } ;
struct afs_fs_cursor {int error; int /*<<< orphan*/  cb_break; int /*<<< orphan*/  cbi; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
typedef  int /*<<< orphan*/  afs_access_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_cache_permit (struct afs_vnode*,struct key*,int /*<<< orphan*/ ,struct afs_status_cb*) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,struct afs_vnode*) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_fs_fetch_file_status (struct afs_fs_cursor*,struct afs_status_cb*,int /*<<< orphan*/ *) ; 
 int afs_inode_init_from_status (struct afs_vnode*,struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 struct afs_status_cb* kzalloc (int,int /*<<< orphan*/ ) ; 

int afs_fetch_status(struct afs_vnode *vnode, struct key *key, bool is_new,
		     afs_access_t *_caller_access)
{
	struct afs_status_cb *scb;
	struct afs_fs_cursor fc;
	int ret;

	_enter("%s,{%llx:%llu.%u,S=%lx}",
	       vnode->volume->name,
	       vnode->fid.vid, vnode->fid.vnode, vnode->fid.unique,
	       vnode->flags);

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_KERNEL);
	if (!scb)
		return -ENOMEM;

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key, true)) {
		afs_dataversion_t data_version = vnode->status.data_version;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			afs_fs_fetch_file_status(&fc, scb, NULL);
		}

		if (fc.error) {
			/* Do nothing. */
		} else if (is_new) {
			ret = afs_inode_init_from_status(vnode, key, fc.cbi,
							 NULL, scb);
			fc.error = ret;
			if (ret == 0)
				afs_cache_permit(vnode, key, fc.cb_break, scb);
		} else {
			afs_vnode_commit_status(&fc, vnode, fc.cb_break,
						&data_version, scb);
		}
		afs_check_for_remote_deletion(&fc, vnode);
		ret = afs_end_vnode_operation(&fc);
	}

	if (ret == 0 && _caller_access)
		*_caller_access = scb->status.caller_access;
	kfree(scb);
	_leave(" = %d", ret);
	return ret;
}