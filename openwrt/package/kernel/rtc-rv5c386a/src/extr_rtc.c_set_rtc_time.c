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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;

/* Variables and functions */
 int I2C_WRITE_MASK ; 
 int RTC_I2C_ADDRESS ; 
 int RTC_Y2K_MASK ; 
 int /*<<< orphan*/  i2c_outb (int) ; 
 int /*<<< orphan*/  i2c_start () ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 void* to_bcd (int) ; 

__attribute__((used)) static void set_rtc_time(struct rtc_time *rtc_tm)
{
	rtc_tm->tm_sec  = to_bcd(rtc_tm->tm_sec);
	rtc_tm->tm_min  = to_bcd(rtc_tm->tm_min);
	rtc_tm->tm_hour = to_bcd(rtc_tm->tm_hour);
	rtc_tm->tm_mday = to_bcd(rtc_tm->tm_mday);
	rtc_tm->tm_mon  = to_bcd(rtc_tm->tm_mon + 1);
	rtc_tm->tm_year = to_bcd(rtc_tm->tm_year);

	if (rtc_tm->tm_year >= 0x100) {
		rtc_tm->tm_year -= 0x100;
		rtc_tm->tm_mon |= RTC_Y2K_MASK;
	}

	spin_lock_irq(&rtc_lock);
	i2c_start();
	i2c_outb(RTC_I2C_ADDRESS | I2C_WRITE_MASK);
	i2c_outb(0x00);	/* set starting register to 0 (=seconds) */
	i2c_outb(rtc_tm->tm_sec);
	i2c_outb(rtc_tm->tm_min);
	i2c_outb(rtc_tm->tm_hour);
	i2c_outb(rtc_tm->tm_wday);
	i2c_outb(rtc_tm->tm_mday);
	i2c_outb(rtc_tm->tm_mon);
	i2c_outb(rtc_tm->tm_year);
	i2c_stop();
	spin_unlock_irq(&rtc_lock);
}