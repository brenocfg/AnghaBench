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
struct TYPE_6__ {int error; } ;
struct afs_fs_cursor {TYPE_3__ ac; TYPE_2__* cbi; } ;
struct TYPE_5__ {TYPE_1__* server; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_PROBED ; 
 int /*<<< orphan*/  AFS_SERVER_FL_PROBING ; 
 int ERESTARTSYS ; 
 int ESTALE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_do_probe_fileserver (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool afs_probe_fileserver(struct afs_fs_cursor *fc)
{
	bool success;
	int ret, retries = 0;

	_enter("");

retry:
	if (test_bit(AFS_SERVER_FL_PROBED, &fc->cbi->server->flags)) {
		_leave(" = t");
		return true;
	}

	if (!test_and_set_bit_lock(AFS_SERVER_FL_PROBING, &fc->cbi->server->flags)) {
		success = afs_do_probe_fileserver(fc);
		clear_bit_unlock(AFS_SERVER_FL_PROBING, &fc->cbi->server->flags);
		wake_up_bit(&fc->cbi->server->flags, AFS_SERVER_FL_PROBING);
		_leave(" = t");
		return success;
	}

	_debug("wait");
	ret = wait_on_bit(&fc->cbi->server->flags, AFS_SERVER_FL_PROBING,
			  TASK_INTERRUPTIBLE);
	if (ret == -ERESTARTSYS) {
		fc->ac.error = ret;
		_leave(" = f [%d]", ret);
		return false;
	}

	retries++;
	if (retries == 4) {
		fc->ac.error = -ESTALE;
		_leave(" = f [stale]");
		return false;
	}
	_debug("retry");
	goto retry;
}