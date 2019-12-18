#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fl_type; scalar_t__ fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_pid; } ;
struct nlm_lock {TYPE_2__ fl; } ;
struct nlm_file {int /*<<< orphan*/  f_file; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,long long) ; 
 TYPE_3__* locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_granted ; 
 int /*<<< orphan*/  nlm_lck_denied_nolocks ; 
 int /*<<< orphan*/  nlmsvc_cancel_blocked (struct net*,struct nlm_file*,struct nlm_lock*) ; 
 int vfs_lock_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__be32
nlmsvc_unlock(struct net *net, struct nlm_file *file, struct nlm_lock *lock)
{
	int	error;

	dprintk("lockd: nlmsvc_unlock(%s/%ld, pi=%d, %Ld-%Ld)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	/* First, cancel any lock that might be there */
	nlmsvc_cancel_blocked(net, file, lock);

	lock->fl.fl_type = F_UNLCK;
	error = vfs_lock_file(file->f_file, F_SETLK, &lock->fl, NULL);

	return (error < 0)? nlm_lck_denied_nolocks : nlm_granted;
}