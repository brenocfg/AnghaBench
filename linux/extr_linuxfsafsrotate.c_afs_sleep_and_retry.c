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
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct afs_fs_cursor {TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool afs_sleep_and_retry(struct afs_fs_cursor *fc)
{
	msleep_interruptible(1000);
	if (signal_pending(current)) {
		fc->ac.error = -ERESTARTSYS;
		return false;
	}

	return true;
}