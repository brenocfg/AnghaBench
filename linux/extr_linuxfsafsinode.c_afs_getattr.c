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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int dummy; } ;
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
struct afs_vnode {int /*<<< orphan*/  cb_lock; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done_seqretry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 scalar_t__ need_seqretry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_seqbegin_or_lock (int /*<<< orphan*/ *,int*) ; 

int afs_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct afs_vnode *vnode = AFS_FS_I(inode);
	int seq = 0;

	_enter("{ ino=%lu v=%u }", inode->i_ino, inode->i_generation);

	do {
		read_seqbegin_or_lock(&vnode->cb_lock, &seq);
		generic_fillattr(inode, stat);
	} while (need_seqretry(&vnode->cb_lock, seq));

	done_seqretry(&vnode->cb_lock, seq);
	return 0;
}