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
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct svc_export {int ex_flags; TYPE_1__ ex_path; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_gid; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int NFSD_MAY_EXEC ; 
 int NFSD_MAY_LOCAL_ACCESS ; 
 int NFSD_MAY_LOCK ; 
 int NFSD_MAY_MASK ; 
 int NFSD_MAY_NOP ; 
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_READ ; 
 int NFSD_MAY_READ_IF_EXEC ; 
 int NFSD_MAY_SATTR ; 
 int NFSD_MAY_TRUNC ; 
 int NFSD_MAY_WRITE ; 
 int NFSEXP_NOAUTHNLM ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ __mnt_is_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dprintk (char*,int,char*,char*,char*,...) ; 
 scalar_t__ exp_rdonly (struct svc_rqst*,struct svc_export*) ; 
 int inode_permission (struct inode*,int) ; 
 int /*<<< orphan*/  nfserr_perm ; 
 int /*<<< orphan*/  nfserr_rofs ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__be32
nfsd_permission(struct svc_rqst *rqstp, struct svc_export *exp,
					struct dentry *dentry, int acc)
{
	struct inode	*inode = d_inode(dentry);
	int		err;

	if ((acc & NFSD_MAY_MASK) == NFSD_MAY_NOP)
		return 0;
#if 0
	dprintk("nfsd: permission 0x%x%s%s%s%s%s%s%s mode 0%o%s%s%s\n",
		acc,
		(acc & NFSD_MAY_READ)?	" read"  : "",
		(acc & NFSD_MAY_WRITE)?	" write" : "",
		(acc & NFSD_MAY_EXEC)?	" exec"  : "",
		(acc & NFSD_MAY_SATTR)?	" sattr" : "",
		(acc & NFSD_MAY_TRUNC)?	" trunc" : "",
		(acc & NFSD_MAY_LOCK)?	" lock"  : "",
		(acc & NFSD_MAY_OWNER_OVERRIDE)? " owneroverride" : "",
		inode->i_mode,
		IS_IMMUTABLE(inode)?	" immut" : "",
		IS_APPEND(inode)?	" append" : "",
		__mnt_is_readonly(exp->ex_path.mnt)?	" ro" : "");
	dprintk("      owner %d/%d user %d/%d\n",
		inode->i_uid, inode->i_gid, current_fsuid(), current_fsgid());
#endif

	/* Normally we reject any write/sattr etc access on a read-only file
	 * system.  But if it is IRIX doing check on write-access for a 
	 * device special file, we ignore rofs.
	 */
	if (!(acc & NFSD_MAY_LOCAL_ACCESS))
		if (acc & (NFSD_MAY_WRITE | NFSD_MAY_SATTR | NFSD_MAY_TRUNC)) {
			if (exp_rdonly(rqstp, exp) ||
			    __mnt_is_readonly(exp->ex_path.mnt))
				return nfserr_rofs;
			if (/* (acc & NFSD_MAY_WRITE) && */ IS_IMMUTABLE(inode))
				return nfserr_perm;
		}
	if ((acc & NFSD_MAY_TRUNC) && IS_APPEND(inode))
		return nfserr_perm;

	if (acc & NFSD_MAY_LOCK) {
		/* If we cannot rely on authentication in NLM requests,
		 * just allow locks, otherwise require read permission, or
		 * ownership
		 */
		if (exp->ex_flags & NFSEXP_NOAUTHNLM)
			return 0;
		else
			acc = NFSD_MAY_READ | NFSD_MAY_OWNER_OVERRIDE;
	}
	/*
	 * The file owner always gets access permission for accesses that
	 * would normally be checked at open time. This is to make
	 * file access work even when the client has done a fchmod(fd, 0).
	 *
	 * However, `cp foo bar' should fail nevertheless when bar is
	 * readonly. A sensible way to do this might be to reject all
	 * attempts to truncate a read-only file, because a creat() call
	 * always implies file truncation.
	 * ... but this isn't really fair.  A process may reasonably call
	 * ftruncate on an open file descriptor on a file with perm 000.
	 * We must trust the client to do permission checking - using "ACCESS"
	 * with NFSv3.
	 */
	if ((acc & NFSD_MAY_OWNER_OVERRIDE) &&
	    uid_eq(inode->i_uid, current_fsuid()))
		return 0;

	/* This assumes  NFSD_MAY_{READ,WRITE,EXEC} == MAY_{READ,WRITE,EXEC} */
	err = inode_permission(inode, acc & (MAY_READ|MAY_WRITE|MAY_EXEC));

	/* Allow read access to binaries even when mode 111 */
	if (err == -EACCES && S_ISREG(inode->i_mode) &&
	     (acc == (NFSD_MAY_READ | NFSD_MAY_OWNER_OVERRIDE) ||
	      acc == (NFSD_MAY_READ | NFSD_MAY_READ_IF_EXEC)))
		err = inode_permission(inode, MAY_EXEC);

	return err? nfserrno(err) : 0;
}