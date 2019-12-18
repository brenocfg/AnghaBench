#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_6__ d_name; } ;
struct TYPE_11__ {scalar_t__ i_nlink; } ;
struct TYPE_7__ {scalar_t__ data_version; } ;
struct afs_vnode {int /*<<< orphan*/  flags; TYPE_5__ vfs_inode; TYPE_1__ status; } ;
struct afs_status_cb {int dummy; } ;
struct TYPE_8__ {scalar_t__ abort_code; int /*<<< orphan*/  error; } ;
struct afs_fs_cursor {int /*<<< orphan*/  cb_break; TYPE_4__* cbi; TYPE_2__ ac; } ;
typedef  scalar_t__ afs_dataversion_t ;
struct TYPE_10__ {TYPE_3__* server; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_IS_YFS ; 
 int /*<<< orphan*/  AFS_SERVER_FL_NO_RM2 ; 
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  AFS_VNODE_DIR_VALID ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RXGEN_OPCODE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ afs_begin_vnode_operation (struct afs_fs_cursor*,struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_calc_vnode_cb_break (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_edit_dir_for_unlink ; 
 int /*<<< orphan*/  afs_edit_dir_remove (struct afs_vnode*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int afs_end_vnode_operation (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_fs_remove (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,int,struct afs_status_cb*) ; 
 scalar_t__ afs_select_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_vnode_commit_status (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,scalar_t__*,struct afs_status_cb*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_nlink (TYPE_5__*) ; 
 struct afs_status_cb* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct afs_status_cb*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_silly_rename (struct afs_vnode*,int) ; 
 int /*<<< orphan*/  yfs_fs_remove_file2 (struct afs_fs_cursor*,struct afs_vnode*,int /*<<< orphan*/ ,struct afs_status_cb*,struct afs_status_cb*) ; 

__attribute__((used)) static int afs_do_silly_unlink(struct afs_vnode *dvnode, struct afs_vnode *vnode,
			       struct dentry *dentry, struct key *key)
{
	struct afs_fs_cursor fc;
	struct afs_status_cb *scb;
	int ret = -ERESTARTSYS;

	_enter("");

	scb = kcalloc(2, sizeof(struct afs_status_cb), GFP_KERNEL);
	if (!scb)
		return -ENOMEM;

	trace_afs_silly_rename(vnode, true);
	if (afs_begin_vnode_operation(&fc, dvnode, key, false)) {
		afs_dataversion_t dir_data_version = dvnode->status.data_version + 1;

		while (afs_select_fileserver(&fc)) {
			fc.cb_break = afs_calc_vnode_cb_break(dvnode);

			if (test_bit(AFS_SERVER_FL_IS_YFS, &fc.cbi->server->flags) &&
			    !test_bit(AFS_SERVER_FL_NO_RM2, &fc.cbi->server->flags)) {
				yfs_fs_remove_file2(&fc, vnode, dentry->d_name.name,
						    &scb[0], &scb[1]);
				if (fc.ac.error != -ECONNABORTED ||
				    fc.ac.abort_code != RXGEN_OPCODE)
					continue;
				set_bit(AFS_SERVER_FL_NO_RM2, &fc.cbi->server->flags);
			}

			afs_fs_remove(&fc, vnode, dentry->d_name.name, false, &scb[0]);
		}

		afs_vnode_commit_status(&fc, dvnode, fc.cb_break,
					&dir_data_version, &scb[0]);
		ret = afs_end_vnode_operation(&fc);
		if (ret == 0) {
			drop_nlink(&vnode->vfs_inode);
			if (vnode->vfs_inode.i_nlink == 0) {
				set_bit(AFS_VNODE_DELETED, &vnode->flags);
				clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
			}
		}
		if (ret == 0 &&
		    test_bit(AFS_VNODE_DIR_VALID, &dvnode->flags))
			afs_edit_dir_remove(dvnode, &dentry->d_name,
					    afs_edit_dir_for_unlink);
	}

	kfree(scb);
	_leave(" = %d", ret);
	return ret;
}