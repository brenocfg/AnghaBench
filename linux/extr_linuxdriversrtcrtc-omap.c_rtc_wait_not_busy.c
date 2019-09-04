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
typedef  int u8 ;
struct omap_rtc {int dummy; } ;

/* Variables and functions */
 int OMAP_RTC_STATUS_BUSY ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 int rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtc_wait_not_busy(struct omap_rtc *rtc)
{
	int count;
	u8 status;

	/* BUSY may stay active for 1/32768 second (~30 usec) */
	for (count = 0; count < 50; count++) {
		status = rtc_read(rtc, OMAP_RTC_STATUS_REG);
		if (!(status & OMAP_RTC_STATUS_BUSY))
			break;
		udelay(1);
	}
	/* now we have ~15 usec to read/write various registers */
}