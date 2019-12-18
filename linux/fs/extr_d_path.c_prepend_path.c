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
struct vfsmount {struct dentry* mnt_root; } ;
struct path {struct vfsmount* mnt; struct dentry* dentry; } ;
struct mount {int /*<<< orphan*/  mnt_ns; struct vfsmount mnt; int /*<<< orphan*/  mnt_mountpoint; int /*<<< orphan*/  mnt_parent; } ;
struct dentry {int /*<<< orphan*/  d_name; struct dentry* d_parent; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  is_anon_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mounted (struct vfsmount*) ; 
 int /*<<< orphan*/  mount_lock ; 
 scalar_t__ need_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  prefetch (struct dentry*) ; 
 int prepend_name (char**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_seqbegin_or_lock (int /*<<< orphan*/ *,unsigned int*) ; 
 struct mount* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  rename_lock ; 

__attribute__((used)) static int prepend_path(const struct path *path,
			const struct path *root,
			char **buffer, int *buflen)
{
	struct dentry *dentry;
	struct vfsmount *vfsmnt;
	struct mount *mnt;
	int error = 0;
	unsigned seq, m_seq = 0;
	char *bptr;
	int blen;

	rcu_read_lock();
restart_mnt:
	read_seqbegin_or_lock(&mount_lock, &m_seq);
	seq = 0;
	rcu_read_lock();
restart:
	bptr = *buffer;
	blen = *buflen;
	error = 0;
	dentry = path->dentry;
	vfsmnt = path->mnt;
	mnt = real_mount(vfsmnt);
	read_seqbegin_or_lock(&rename_lock, &seq);
	while (dentry != root->dentry || vfsmnt != root->mnt) {
		struct dentry * parent;

		if (dentry == vfsmnt->mnt_root || IS_ROOT(dentry)) {
			struct mount *parent = READ_ONCE(mnt->mnt_parent);
			/* Escaped? */
			if (dentry != vfsmnt->mnt_root) {
				bptr = *buffer;
				blen = *buflen;
				error = 3;
				break;
			}
			/* Global root? */
			if (mnt != parent) {
				dentry = READ_ONCE(mnt->mnt_mountpoint);
				mnt = parent;
				vfsmnt = &mnt->mnt;
				continue;
			}
			if (is_mounted(vfsmnt) && !is_anon_ns(mnt->mnt_ns))
				error = 1;	// absolute root
			else
				error = 2;	// detached or not attached yet
			break;
		}
		parent = dentry->d_parent;
		prefetch(parent);
		error = prepend_name(&bptr, &blen, &dentry->d_name);
		if (error)
			break;

		dentry = parent;
	}
	if (!(seq & 1))
		rcu_read_unlock();
	if (need_seqretry(&rename_lock, seq)) {
		seq = 1;
		goto restart;
	}
	done_seqretry(&rename_lock, seq);

	if (!(m_seq & 1))
		rcu_read_unlock();
	if (need_seqretry(&mount_lock, m_seq)) {
		m_seq = 1;
		goto restart_mnt;
	}
	done_seqretry(&mount_lock, m_seq);

	if (error >= 0 && bptr == *buffer) {
		if (--blen < 0)
			error = -ENAMETOOLONG;
		else
			*--bptr = '/';
	}
	*buffer = bptr;
	*buflen = blen;
	return error;
}