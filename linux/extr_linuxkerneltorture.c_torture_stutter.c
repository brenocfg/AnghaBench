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

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int stutter ; 
 int /*<<< orphan*/  stutter_pause_test ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int /*<<< orphan*/  torture_shutdown_absorb (char*) ; 

__attribute__((used)) static int torture_stutter(void *arg)
{
	VERBOSE_TOROUT_STRING("torture_stutter task started");
	do {
		if (!torture_must_stop() && stutter > 1) {
			WRITE_ONCE(stutter_pause_test, 1);
			schedule_timeout_interruptible(stutter - 1);
			WRITE_ONCE(stutter_pause_test, 2);
			schedule_timeout_interruptible(1);
		}
		WRITE_ONCE(stutter_pause_test, 0);
		if (!torture_must_stop())
			schedule_timeout_interruptible(stutter);
		torture_shutdown_absorb("torture_stutter");
	} while (!torture_must_stop());
	torture_kthread_stopping("torture_stutter");
	return 0;
}