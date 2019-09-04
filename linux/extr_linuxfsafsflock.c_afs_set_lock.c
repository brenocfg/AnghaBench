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
struct key {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; TYPE_2__* volume; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; int /*<<< orphan*/  vnode; } ;
typedef  int /*<<< orphan*/  afs_lock_type_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,int /*<<< orphan*/ ) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_fs_set_lock (struct afs_fs_cursor*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 

__attribute__((used)) static int afs_set_lock(struct afs_vnode *vnode, struct key *key,
			afs_lock_type_t type)
{
	struct afs_fs_cursor fc;
	int ret;

	_enter("%s{%x:%u.%u},%x,%u",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key), type);

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key)) {
		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			afs_fs_set_lock(&fc, type);
		}

		afs_check_for_remote_deletion(&fc, fc.vnode);
		afs_vnode_commit_status(&fc, vnode, fc.cb_break);
		ret = afs_end_vnode_operation(&fc);
	}

	_leave(" = %d", ret);
	return ret;
}