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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file_lock {int dummy; } ;
struct file {struct cifsFileInfo* private_data; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
struct TYPE_2__ {scalar_t__ local_lease; } ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ CIFS_CACHE_WRITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_I (struct inode*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 long F_RDLCK ; 
 long F_UNLCK ; 
 long F_WRLCK ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int generic_setlease (struct file*,long,struct file_lock**,void**) ; 
 TYPE_1__* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_setlease(struct file *file, long arg, struct file_lock **lease, void **priv)
{
	/*
	 * Note that this is called by vfs setlease with i_lock held to
	 * protect *lease from going away.
	 */
	struct inode *inode = file_inode(file);
	struct cifsFileInfo *cfile = file->private_data;

	if (!(S_ISREG(inode->i_mode)))
		return -EINVAL;

	/* Check if file is oplocked if this is request for new lease */
	if (arg == F_UNLCK ||
	    ((arg == F_RDLCK) && CIFS_CACHE_READ(CIFS_I(inode))) ||
	    ((arg == F_WRLCK) && CIFS_CACHE_WRITE(CIFS_I(inode))))
		return generic_setlease(file, arg, lease, priv);
	else if (tlink_tcon(cfile->tlink)->local_lease &&
		 !CIFS_CACHE_READ(CIFS_I(inode)))
		/*
		 * If the server claims to support oplock on this file, then we
		 * still need to check oplock even if the local_lease mount
		 * option is set, but there are servers which do not support
		 * oplock for which this mount option may be useful if the user
		 * knows that the file won't be changed on the server by anyone
		 * else.
		 */
		return generic_setlease(file, arg, lease, priv);
	else
		return -EAGAIN;
}