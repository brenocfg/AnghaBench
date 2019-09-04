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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int time64_t ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_AL0 ; 
 int /*<<< orphan*/  AB3100_AL1 ; 
 int /*<<< orphan*/  AB3100_AL2 ; 
 int /*<<< orphan*/  AB3100_AL3 ; 
 int /*<<< orphan*/  AB3100_RTC ; 
 int AB3100_RTC_CLOCK_RATE ; 
 int abx500_mask_and_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab3100_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	u8 regs[] = {AB3100_AL0, AB3100_AL1, AB3100_AL2, AB3100_AL3};
	unsigned char buf[4];
	time64_t secs;
	u64 hw_counter;
	int err;
	int i;

	secs = rtc_tm_to_time64(&alarm->time);
	hw_counter = secs * AB3100_RTC_CLOCK_RATE * 2;
	buf[0] = (hw_counter >> 16) & 0xFF;
	buf[1] = (hw_counter >> 24) & 0xFF;
	buf[2] = (hw_counter >> 32) & 0xFF;
	buf[3] = (hw_counter >> 40) & 0xFF;

	/* Set the alarm */
	for (i = 0; i < 4; i++) {
		err = abx500_set_register_interruptible(dev, 0,
							regs[i], buf[i]);
		if (err)
			return err;
	}
	/* Then enable the alarm */
	return abx500_mask_and_set_register_interruptible(dev, 0,
							  AB3100_RTC, (1 << 2),
							  alarm->enabled << 2);
}