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
struct afs_vnode {TYPE_3__ status; TYPE_2__ fid; TYPE_1__* volume; } ;
struct afs_status_cb {int dummy; } ;
struct afs_read {int /*<<< orphan*/  actual_len; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
struct TYPE_8__ {int /*<<< orphan*/  n_fetch_bytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_check_for_remote_deletion (struct afs_fs_cursor*,struct afs_vnode*) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_fs_fetch_data (struct afs_fs_cursor*,struct afs_status_cb*,struct afs_read*) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_stat_v (struct afs_vnode*,int /*<<< orphan*/ ) ; 
 TYPE_4__* afs_v2net (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afs_status_cb*) ; 
 int /*<<< orphan*/  atomic_long_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 struct afs_status_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_fetches ; 

int afs_fetch_data(struct afs_vnode *vnode, struct key *key, struct afs_read *desc)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	int ret;

	_enter("%s{%llx:%llu.%u},%x,,,",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key));

	scb = kzalloc(sizeof(struct afs_status_cb), GFP_KERNEL);
	if (!scb)
		return -ENOMEM;

	ret = -ERESTARTSYS;
	if (afs_begin_vnode_operation(&fc, vnode, key, true)) {
		afs_dataversion_t data_version = vnode->status.data_version;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(vnode);
			afs_fs_fetch_data(&fc, scb, desc);
		}

		afs_check_for_remote_deletion(&fc, vnode);
		afs_vnode_commit_status(&fc, vnode, fc.cb_break,
					&data_version, scb);
		ret = afs_end_vnode_operation(&fc);
	}

	if (ret == 0) {
		afs_stat_v(vnode, n_fetches);
		atomic_long_add(desc->actual_len,
				&afs_v2net(vnode)->n_fetch_bytes);
	}

	kfree(scb);
	_leave(" = %d", ret);
	return ret;
}