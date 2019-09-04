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
struct TYPE_6__ {int oflags; } ;
typedef  TYPE_2__ xfs_fsop_handlereq_t ;
struct path {struct file* dentry; int /*<<< orphan*/  mnt; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  mnt; } ;
struct file {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  f_flags; TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  f_flags; TYPE_1__ f_path; } ;
struct cred {int dummy; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EISDIR ; 
 int EPERM ; 
 int /*<<< orphan*/  FMODE_NOCMTIME ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int OPEN_FMODE (int) ; 
 int O_APPEND ; 
 int O_LARGEFILE ; 
 int /*<<< orphan*/  O_NOATIME ; 
 int O_TRUNC ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 struct inode* d_inode (struct file*) ; 
 struct file* dentry_open (struct path*,int,struct cred const*) ; 
 int /*<<< orphan*/  dput (struct file*) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 struct file* xfs_handlereq_to_dentry (struct file*,TYPE_2__*) ; 

int
xfs_open_by_handle(
	struct file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
{
	const struct cred	*cred = current_cred();
	int			error;
	int			fd;
	int			permflag;
	struct file		*filp;
	struct inode		*inode;
	struct dentry		*dentry;
	fmode_t			fmode;
	struct path		path;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	dentry = xfs_handlereq_to_dentry(parfilp, hreq);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);
	inode = d_inode(dentry);

	/* Restrict xfs_open_by_handle to directories & regular files. */
	if (!(S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode))) {
		error = -EPERM;
		goto out_dput;
	}

#if BITS_PER_LONG != 32
	hreq->oflags |= O_LARGEFILE;
#endif

	permflag = hreq->oflags;
	fmode = OPEN_FMODE(permflag);
	if ((!(permflag & O_APPEND) || (permflag & O_TRUNC)) &&
	    (fmode & FMODE_WRITE) && IS_APPEND(inode)) {
		error = -EPERM;
		goto out_dput;
	}

	if ((fmode & FMODE_WRITE) && IS_IMMUTABLE(inode)) {
		error = -EPERM;
		goto out_dput;
	}

	/* Can't write directories. */
	if (S_ISDIR(inode->i_mode) && (fmode & FMODE_WRITE)) {
		error = -EISDIR;
		goto out_dput;
	}

	fd = get_unused_fd_flags(0);
	if (fd < 0) {
		error = fd;
		goto out_dput;
	}

	path.mnt = parfilp->f_path.mnt;
	path.dentry = dentry;
	filp = dentry_open(&path, hreq->oflags, cred);
	dput(dentry);
	if (IS_ERR(filp)) {
		put_unused_fd(fd);
		return PTR_ERR(filp);
	}

	if (S_ISREG(inode->i_mode)) {
		filp->f_flags |= O_NOATIME;
		filp->f_mode |= FMODE_NOCMTIME;
	}

	fd_install(fd, filp);
	return fd;

 out_dput:
	dput(dentry);
	return error;
}