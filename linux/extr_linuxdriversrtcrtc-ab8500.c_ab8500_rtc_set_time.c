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
struct rtc_time {int tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int AB8500_RTC_EPOCH ; 
 int /*<<< orphan*/  AB8500_RTC_READ_REQ_REG ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned long COUNTS_PER_SEC ; 
 int EINVAL ; 
 unsigned char RTC_WRITE_REQUEST ; 
 int /*<<< orphan*/ * ab8500_rtc_time_regs ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 scalar_t__ get_elapsed_seconds (int) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int ab8500_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	int retval, i;
	unsigned char buf[ARRAY_SIZE(ab8500_rtc_time_regs)];
	unsigned long no_secs, no_mins, secs = 0;

	if (tm->tm_year < (AB8500_RTC_EPOCH - 1900)) {
		dev_dbg(dev, "year should be equal to or greater than %d\n",
				AB8500_RTC_EPOCH);
		return -EINVAL;
	}

	/* Get the number of seconds since 1970 */
	rtc_tm_to_time(tm, &secs);

	/*
	 * Convert it to the number of seconds since 01-01-2000 00:00:00, since
	 * we only have a small counter in the RTC.
	 */
	secs -= get_elapsed_seconds(AB8500_RTC_EPOCH);

	no_mins = secs / 60;

	no_secs = secs % 60;
	/* Make the seconds count as per the RTC resolution */
	no_secs = no_secs * COUNTS_PER_SEC;

	buf[4] = no_secs & 0xFF;
	buf[3] = (no_secs >> 8) & 0xFF;

	buf[2] = no_mins & 0xFF;
	buf[1] = (no_mins >> 8) & 0xFF;
	buf[0] = (no_mins >> 16) & 0xFF;

	for (i = 0; i < ARRAY_SIZE(ab8500_rtc_time_regs); i++) {
		retval = abx500_set_register_interruptible(dev, AB8500_RTC,
			ab8500_rtc_time_regs[i], buf[i]);
		if (retval < 0)
			return retval;
	}

	/* Request a data write */
	return abx500_set_register_interruptible(dev, AB8500_RTC,
		AB8500_RTC_READ_REQ_REG, RTC_WRITE_REQUEST);
}