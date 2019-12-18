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
struct afs_fs_cursor {int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int AFS_FS_CURSOR_INTR ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool afs_sleep_and_retry(struct afs_fs_cursor *fc)
{
	if (fc->flags & AFS_FS_CURSOR_INTR) {
		msleep_interruptible(1000);
		if (signal_pending(current)) {
			fc->error = -ERESTARTSYS;
			return false;
		}
	} else {
		msleep(1000);
	}

	return true;
}