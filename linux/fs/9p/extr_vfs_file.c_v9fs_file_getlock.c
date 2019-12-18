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
struct p9_getlock {int type; scalar_t__ start; scalar_t__ length; scalar_t__ client_id; int /*<<< orphan*/  proc_id; } ;
struct p9_fid {TYPE_1__* clnt; } ;
struct file_lock {scalar_t__ fl_type; scalar_t__ fl_start; scalar_t__ fl_end; int /*<<< orphan*/  fl_pid; } ;
struct file {struct p9_fid* private_data; } ;
typedef  int /*<<< orphan*/  glock ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 scalar_t__ OFFSET_MAX ; 
#define  P9_LOCK_TYPE_RDLCK 130 
#define  P9_LOCK_TYPE_UNLCK 129 
#define  P9_LOCK_TYPE_WRLCK 128 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct p9_getlock*,int /*<<< orphan*/ ,int) ; 
 int p9_client_getlock_dotl (struct p9_fid*,struct p9_getlock*) ; 
 int /*<<< orphan*/  posix_test_lock (struct file*,struct file_lock*) ; 

__attribute__((used)) static int v9fs_file_getlock(struct file *filp, struct file_lock *fl)
{
	struct p9_getlock glock;
	struct p9_fid *fid;
	int res = 0;

	fid = filp->private_data;
	BUG_ON(fid == NULL);

	posix_test_lock(filp, fl);
	/*
	 * if we have a conflicting lock locally, no need to validate
	 * with server
	 */
	if (fl->fl_type != F_UNLCK)
		return res;

	/* convert posix lock to p9 tgetlock args */
	memset(&glock, 0, sizeof(glock));
	glock.type  = P9_LOCK_TYPE_UNLCK;
	glock.start = fl->fl_start;
	if (fl->fl_end == OFFSET_MAX)
		glock.length = 0;
	else
		glock.length = fl->fl_end - fl->fl_start + 1;
	glock.proc_id = fl->fl_pid;
	glock.client_id = fid->clnt->name;

	res = p9_client_getlock_dotl(fid, &glock);
	if (res < 0)
		goto out;
	/* map 9p lock type to os lock type */
	switch (glock.type) {
	case P9_LOCK_TYPE_RDLCK:
		fl->fl_type = F_RDLCK;
		break;
	case P9_LOCK_TYPE_WRLCK:
		fl->fl_type = F_WRLCK;
		break;
	case P9_LOCK_TYPE_UNLCK:
		fl->fl_type = F_UNLCK;
		break;
	}
	if (glock.type != P9_LOCK_TYPE_UNLCK) {
		fl->fl_start = glock.start;
		if (glock.length == 0)
			fl->fl_end = OFFSET_MAX;
		else
			fl->fl_end = glock.start + glock.length - 1;
		fl->fl_pid = -glock.proc_id;
	}
out:
	if (glock.client_id != fid->clnt->name)
		kfree(glock.client_id);
	return res;
}