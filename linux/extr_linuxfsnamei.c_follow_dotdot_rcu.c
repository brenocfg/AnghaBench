#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct dentry* dentry; TYPE_1__* mnt; } ;
struct nameidata {unsigned int seq; struct inode* inode; TYPE_2__ path; int /*<<< orphan*/  m_seq; int /*<<< orphan*/  root; } ;
struct TYPE_5__ {struct dentry* mnt_root; } ;
struct mount {TYPE_1__ mnt; struct dentry* mnt_mountpoint; struct mount* mnt_parent; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_seq; struct inode* d_inode; struct dentry* d_parent; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 struct mount* __lookup_mnt (TYPE_1__*,struct dentry*) ; 
 int d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  mount_lock ; 
 int /*<<< orphan*/  path_connected (TYPE_2__*) ; 
 scalar_t__ path_equal (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* read_seqcount_begin (int /*<<< orphan*/ *) ; 
 int read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int read_seqretry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mount* real_mount (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int follow_dotdot_rcu(struct nameidata *nd)
{
	struct inode *inode = nd->inode;

	while (1) {
		if (path_equal(&nd->path, &nd->root))
			break;
		if (nd->path.dentry != nd->path.mnt->mnt_root) {
			struct dentry *old = nd->path.dentry;
			struct dentry *parent = old->d_parent;
			unsigned seq;

			inode = parent->d_inode;
			seq = read_seqcount_begin(&parent->d_seq);
			if (unlikely(read_seqcount_retry(&old->d_seq, nd->seq)))
				return -ECHILD;
			nd->path.dentry = parent;
			nd->seq = seq;
			if (unlikely(!path_connected(&nd->path)))
				return -ENOENT;
			break;
		} else {
			struct mount *mnt = real_mount(nd->path.mnt);
			struct mount *mparent = mnt->mnt_parent;
			struct dentry *mountpoint = mnt->mnt_mountpoint;
			struct inode *inode2 = mountpoint->d_inode;
			unsigned seq = read_seqcount_begin(&mountpoint->d_seq);
			if (unlikely(read_seqretry(&mount_lock, nd->m_seq)))
				return -ECHILD;
			if (&mparent->mnt == nd->path.mnt)
				break;
			/* we know that mountpoint was pinned */
			nd->path.dentry = mountpoint;
			nd->path.mnt = &mparent->mnt;
			inode = inode2;
			nd->seq = seq;
		}
	}
	while (unlikely(d_mountpoint(nd->path.dentry))) {
		struct mount *mounted;
		mounted = __lookup_mnt(nd->path.mnt, nd->path.dentry);
		if (unlikely(read_seqretry(&mount_lock, nd->m_seq)))
			return -ECHILD;
		if (!mounted)
			break;
		nd->path.mnt = &mounted->mnt;
		nd->path.dentry = mounted->mnt.mnt_root;
		inode = nd->path.dentry->d_inode;
		nd->seq = read_seqcount_begin(&nd->path.dentry->d_seq);
	}
	nd->inode = inode;
	return 0;
}