#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct afs_vnode {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct afs_fs_cursor {TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  afs_break_callback (struct afs_vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_cb_break_for_deleted ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void afs_check_for_remote_deletion(struct afs_fs_cursor *fc,
						 struct afs_vnode *vnode)
{
	if (fc->ac.error == -ENOENT) {
		set_bit(AFS_VNODE_DELETED, &vnode->flags);
		afs_break_callback(vnode, afs_cb_break_for_deleted);
	}
}