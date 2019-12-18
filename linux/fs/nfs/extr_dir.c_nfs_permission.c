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
struct inode {int i_mode; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  access; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ECHILD ; 
 int MAY_ACCESS ; 
 int MAY_CHDIR ; 
 int MAY_EXEC ; 
 int MAY_NOT_BLOCK ; 
 int MAY_OPEN ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  NFSIOS_VFSACCESS ; 
 int /*<<< orphan*/  NFS_CAP_ATOMIC_OPEN ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  VFS ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int generic_permission (struct inode*,int) ; 
 int nfs_do_access (struct inode*,struct cred const*,int) ; 
 int nfs_execute_ok (struct inode*,int) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int nfs_permission(struct inode *inode, int mask)
{
	const struct cred *cred = current_cred();
	int res = 0;

	nfs_inc_stats(inode, NFSIOS_VFSACCESS);

	if ((mask & (MAY_READ | MAY_WRITE | MAY_EXEC)) == 0)
		goto out;
	/* Is this sys_access() ? */
	if (mask & (MAY_ACCESS | MAY_CHDIR))
		goto force_lookup;

	switch (inode->i_mode & S_IFMT) {
		case S_IFLNK:
			goto out;
		case S_IFREG:
			if ((mask & MAY_OPEN) &&
			   nfs_server_capable(inode, NFS_CAP_ATOMIC_OPEN))
				return 0;
			break;
		case S_IFDIR:
			/*
			 * Optimize away all write operations, since the server
			 * will check permissions when we perform the op.
			 */
			if ((mask & MAY_WRITE) && !(mask & MAY_READ))
				goto out;
	}

force_lookup:
	if (!NFS_PROTO(inode)->access)
		goto out_notsup;

	/* Always try fast lookups first */
	rcu_read_lock();
	res = nfs_do_access(inode, cred, mask|MAY_NOT_BLOCK);
	rcu_read_unlock();
	if (res == -ECHILD && !(mask & MAY_NOT_BLOCK)) {
		/* Fast lookup failed, try the slow way */
		res = nfs_do_access(inode, cred, mask);
	}
out:
	if (!res && (mask & MAY_EXEC))
		res = nfs_execute_ok(inode, mask);

	dfprintk(VFS, "NFS: permission(%s/%lu), mask=0x%x, res=%d\n",
		inode->i_sb->s_id, inode->i_ino, mask, res);
	return res;
out_notsup:
	if (mask & MAY_NOT_BLOCK)
		return -ECHILD;

	res = nfs_revalidate_inode(NFS_SERVER(inode), inode);
	if (res == 0)
		res = generic_permission(inode, mask);
	goto out;
}