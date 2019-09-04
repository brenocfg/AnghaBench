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
struct inode {int dummy; } ;
struct file_lock {int fl_type; int fl_flags; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOLCK ; 
 int FL_FLOCK ; 
 int F_UNLCK ; 
 int LOCK_MAND ; 
 int NFS_MOUNT_LOCAL_FLOCK ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int do_setlk (struct file*,int,struct file_lock*,int) ; 
 int do_unlk (struct file*,int,struct file_lock*,int) ; 
 int /*<<< orphan*/  dprintk (char*,struct file*,int,int) ; 

int nfs_flock(struct file *filp, int cmd, struct file_lock *fl)
{
	struct inode *inode = filp->f_mapping->host;
	int is_local = 0;

	dprintk("NFS: flock(%pD2, t=%x, fl=%x)\n",
			filp, fl->fl_type, fl->fl_flags);

	if (!(fl->fl_flags & FL_FLOCK))
		return -ENOLCK;

	/*
	 * The NFSv4 protocol doesn't support LOCK_MAND, which is not part of
	 * any standard. In principle we might be able to support LOCK_MAND
	 * on NFSv2/3 since NLMv3/4 support DOS share modes, but for now the
	 * NFS code is not set up for it.
	 */
	if (fl->fl_type & LOCK_MAND)
		return -EINVAL;

	if (NFS_SERVER(inode)->flags & NFS_MOUNT_LOCAL_FLOCK)
		is_local = 1;

	/* We're simulating flock() locks using posix locks on the server */
	if (fl->fl_type == F_UNLCK)
		return do_unlk(filp, cmd, fl, is_local);
	return do_setlk(filp, cmd, fl, is_local);
}