#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct nlm_lockowner {int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {scalar_t__ fl_type; int /*<<< orphan*/ * fl_owner; scalar_t__ fl_end; scalar_t__ fl_start; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct nlm_lock {char* caller; TYPE_3__ fl; int /*<<< orphan*/  svid; TYPE_2__ oh; int /*<<< orphan*/  len; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {int /*<<< orphan*/  f_file; } ;
struct nlm_cookie {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_9__ {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int FILE_LOCK_DEFERRED ; 
 scalar_t__ F_UNLCK ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,long long,long long,...) ; 
 scalar_t__ locks_in_grace (int /*<<< orphan*/ ) ; 
 TYPE_5__* locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_release_private (TYPE_3__*) ; 
 int /*<<< orphan*/  nlm_granted ; 
 int /*<<< orphan*/  nlm_lck_denied ; 
 int /*<<< orphan*/  nlm_lck_denied_grace_period ; 
 int /*<<< orphan*/  nlm_lck_denied_nolocks ; 
 int /*<<< orphan*/  nlmsvc_put_lockowner (struct nlm_lockowner*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int vfs_test_lock (int /*<<< orphan*/ ,TYPE_3__*) ; 

__be32
nlmsvc_testlock(struct svc_rqst *rqstp, struct nlm_file *file,
		struct nlm_host *host, struct nlm_lock *lock,
		struct nlm_lock *conflock, struct nlm_cookie *cookie)
{
	int			error;
	__be32			ret;
	struct nlm_lockowner	*test_owner;

	dprintk("lockd: nlmsvc_testlock(%s/%ld, ty=%d, %Ld-%Ld)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_type,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	if (locks_in_grace(SVC_NET(rqstp))) {
		ret = nlm_lck_denied_grace_period;
		goto out;
	}

	/* If there's a conflicting lock, remember to clean up the test lock */
	test_owner = (struct nlm_lockowner *)lock->fl.fl_owner;

	error = vfs_test_lock(file->f_file, &lock->fl);
	if (error) {
		/* We can't currently deal with deferred test requests */
		if (error == FILE_LOCK_DEFERRED)
			WARN_ON_ONCE(1);

		ret = nlm_lck_denied_nolocks;
		goto out;
	}

	if (lock->fl.fl_type == F_UNLCK) {
		ret = nlm_granted;
		goto out;
	}

	dprintk("lockd: conflicting lock(ty=%d, %Ld-%Ld)\n",
		lock->fl.fl_type, (long long)lock->fl.fl_start,
		(long long)lock->fl.fl_end);
	conflock->caller = "somehost";	/* FIXME */
	conflock->len = strlen(conflock->caller);
	conflock->oh.len = 0;		/* don't return OH info */
	conflock->svid = ((struct nlm_lockowner *)lock->fl.fl_owner)->pid;
	conflock->fl.fl_type = lock->fl.fl_type;
	conflock->fl.fl_start = lock->fl.fl_start;
	conflock->fl.fl_end = lock->fl.fl_end;
	locks_release_private(&lock->fl);

	/* Clean up the test lock */
	lock->fl.fl_owner = NULL;
	nlmsvc_put_lockowner(test_owner);

	ret = nlm_lck_denied;
out:
	return ret;
}