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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  torture_shutdown_absorb (char*) ; 

void torture_kthread_stopping(char *title)
{
	char buf[128];

	snprintf(buf, sizeof(buf), "Stopping %s", title);
	VERBOSE_TOROUT_STRING(buf);
	while (!kthread_should_stop()) {
		torture_shutdown_absorb(title);
		schedule_timeout_uninterruptible(1);
	}
}