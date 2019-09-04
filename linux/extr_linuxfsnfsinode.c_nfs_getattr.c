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
typedef  int u32 ;
struct path {int /*<<< orphan*/  dentry; TYPE_1__* mnt; } ;
struct nfs_server {int flags; int /*<<< orphan*/  dtsize; } ;
struct kstat {int result_mask; int /*<<< orphan*/  blksize; int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {int /*<<< orphan*/  cache_validity; } ;
struct TYPE_3__ {int mnt_flags; } ;

/* Variables and functions */
 unsigned int AT_STATX_DONT_SYNC ; 
 unsigned int AT_STATX_FORCE_SYNC ; 
 int MNT_NOATIME ; 
 int MNT_NODIRATIME ; 
 int /*<<< orphan*/  NFS_FILEID (struct inode*) ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 unsigned long NFS_INO_INVALID_ATIME ; 
 unsigned long NFS_INO_INVALID_ATTR ; 
 unsigned long NFS_INO_INVALID_LABEL ; 
 unsigned long NFS_INO_REVAL_PAGECACHE ; 
 int NFS_MOUNT_NOAC ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int STATX_ATIME ; 
 int STATX_BLOCKS ; 
 int STATX_CTIME ; 
 int STATX_GID ; 
 int STATX_MODE ; 
 int STATX_MTIME ; 
 int STATX_NLINK ; 
 int STATX_SIZE ; 
 int STATX_UID ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 scalar_t__ nfs_attribute_cache_expired (struct inode*) ; 
 int /*<<< orphan*/  nfs_compat_user_ino64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_readdirplus_parent_cache_hit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_readdirplus_parent_cache_miss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfs_getattr_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_getattr_exit (struct inode*,int) ; 

int nfs_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct nfs_server *server = NFS_SERVER(inode);
	unsigned long cache_validity;
	int err = 0;
	bool force_sync = query_flags & AT_STATX_FORCE_SYNC;
	bool do_update = false;

	trace_nfs_getattr_enter(inode);

	if ((query_flags & AT_STATX_DONT_SYNC) && !force_sync)
		goto out_no_update;

	/* Flush out writes to the server in order to update c/mtime.  */
	if ((request_mask & (STATX_CTIME|STATX_MTIME)) &&
			S_ISREG(inode->i_mode)) {
		err = filemap_write_and_wait(inode->i_mapping);
		if (err)
			goto out;
	}

	/*
	 * We may force a getattr if the user cares about atime.
	 *
	 * Note that we only have to check the vfsmount flags here:
	 *  - NFS always sets S_NOATIME by so checking it would give a
	 *    bogus result
	 *  - NFS never sets SB_NOATIME or SB_NODIRATIME so there is
	 *    no point in checking those.
	 */
	if ((path->mnt->mnt_flags & MNT_NOATIME) ||
	    ((path->mnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode)))
		request_mask &= ~STATX_ATIME;

	/* Is the user requesting attributes that might need revalidation? */
	if (!(request_mask & (STATX_MODE|STATX_NLINK|STATX_ATIME|STATX_CTIME|
					STATX_MTIME|STATX_UID|STATX_GID|
					STATX_SIZE|STATX_BLOCKS)))
		goto out_no_revalidate;

	/* Check whether the cached attributes are stale */
	do_update |= force_sync || nfs_attribute_cache_expired(inode);
	cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);
	do_update |= cache_validity &
		(NFS_INO_INVALID_ATTR|NFS_INO_INVALID_LABEL);
	if (request_mask & STATX_ATIME)
		do_update |= cache_validity & NFS_INO_INVALID_ATIME;
	if (request_mask & (STATX_CTIME|STATX_MTIME))
		do_update |= cache_validity & NFS_INO_REVAL_PAGECACHE;
	if (do_update) {
		/* Update the attribute cache */
		if (!(server->flags & NFS_MOUNT_NOAC))
			nfs_readdirplus_parent_cache_miss(path->dentry);
		else
			nfs_readdirplus_parent_cache_hit(path->dentry);
		err = __nfs_revalidate_inode(server, inode);
		if (err)
			goto out;
	} else
		nfs_readdirplus_parent_cache_hit(path->dentry);
out_no_revalidate:
	/* Only return attributes that were revalidated. */
	stat->result_mask &= request_mask;
out_no_update:
	generic_fillattr(inode, stat);
	stat->ino = nfs_compat_user_ino64(NFS_FILEID(inode));
	if (S_ISDIR(inode->i_mode))
		stat->blksize = NFS_SERVER(inode)->dtsize;
out:
	trace_nfs_getattr_exit(inode, err);
	return err;
}