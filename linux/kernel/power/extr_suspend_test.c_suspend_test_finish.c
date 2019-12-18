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
 int TEST_SUSPEND_SECONDS ; 
 int /*<<< orphan*/  WARN (int,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  abs (long) ; 
 long jiffies ; 
 unsigned int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,unsigned int,unsigned int) ; 
 long suspend_test_start_time ; 

void suspend_test_finish(const char *label)
{
	long nj = jiffies - suspend_test_start_time;
	unsigned msec;

	msec = jiffies_to_msecs(abs(nj));
	pr_info("PM: %s took %d.%03d seconds\n", label,
			msec / 1000, msec % 1000);

	/* Warning on suspend means the RTC alarm period needs to be
	 * larger -- the system was sooo slooowwww to suspend that the
	 * alarm (should have) fired before the system went to sleep!
	 *
	 * Warning on either suspend or resume also means the system
	 * has some performance issues.  The stack dump of a WARN_ON
	 * is more likely to get the right attention than a printk...
	 */
	WARN(msec > (TEST_SUSPEND_SECONDS * 1000),
	     "Component: %s, time: %u\n", label, msec);
}