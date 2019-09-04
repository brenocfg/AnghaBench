#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct key {int dummy; } ;
struct afs_volume {scalar_t__ update_at; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VOLUME_NEEDS_UPDATE ; 
 int /*<<< orphan*/  AFS_VOLUME_UPDATING ; 
 int /*<<< orphan*/  AFS_VOLUME_WAIT ; 
 int ERESTARTSYS ; 
 int ESTALE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_update_volume_status (struct afs_volume*,struct key*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int afs_check_volume_status(struct afs_volume *volume, struct key *key)
{
	time64_t now = ktime_get_real_seconds();
	int ret, retries = 0;

	_enter("");

	if (volume->update_at <= now)
		set_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags);

retry:
	if (!test_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags) &&
	    !test_bit(AFS_VOLUME_WAIT, &volume->flags)) {
		_leave(" = 0");
		return 0;
	}

	if (!test_and_set_bit_lock(AFS_VOLUME_UPDATING, &volume->flags)) {
		ret = afs_update_volume_status(volume, key);
		clear_bit_unlock(AFS_VOLUME_WAIT, &volume->flags);
		clear_bit_unlock(AFS_VOLUME_UPDATING, &volume->flags);
		wake_up_bit(&volume->flags, AFS_VOLUME_WAIT);
		_leave(" = %d", ret);
		return ret;
	}

	if (!test_bit(AFS_VOLUME_WAIT, &volume->flags)) {
		_leave(" = 0 [no wait]");
		return 0;
	}

	ret = wait_on_bit(&volume->flags, AFS_VOLUME_WAIT, TASK_INTERRUPTIBLE);
	if (ret == -ERESTARTSYS) {
		_leave(" = %d", ret);
		return ret;
	}

	retries++;
	if (retries == 4) {
		_leave(" = -ESTALE");
		return -ESTALE;
	}
	goto retry;
}