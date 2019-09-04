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
 scalar_t__ FULLSTOP_SHUTDOWN ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullstop ; 
 int /*<<< orphan*/  pr_notice (char*,char const*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 

void torture_shutdown_absorb(const char *title)
{
	while (READ_ONCE(fullstop) == FULLSTOP_SHUTDOWN) {
		pr_notice("torture thread %s parking due to system shutdown\n",
			  title);
		schedule_timeout_uninterruptible(MAX_SCHEDULE_TIMEOUT);
	}
}