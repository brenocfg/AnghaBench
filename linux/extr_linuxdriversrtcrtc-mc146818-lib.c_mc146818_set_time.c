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
struct rtc_time {unsigned int tm_year; int tm_mon; unsigned char tm_mday; unsigned char tm_hour; unsigned char tm_min; unsigned char tm_sec; } ;

/* Variables and functions */
 unsigned char CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (unsigned char,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_DAY_OF_MONTH ; 
 unsigned char RTC_DIV_RESET2 ; 
 unsigned char RTC_DM_BINARY ; 
 int /*<<< orphan*/  RTC_FREQ_SELECT ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 unsigned char RTC_SET ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 void* bin2bcd (unsigned char) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mc146818_set_time(struct rtc_time *time)
{
	unsigned long flags;
	unsigned char mon, day, hrs, min, sec;
	unsigned char save_control, save_freq_select;
	unsigned int yrs;
#ifdef CONFIG_MACH_DECSTATION
	unsigned int real_yrs, leap_yr;
#endif
	unsigned char century = 0;

	yrs = time->tm_year;
	mon = time->tm_mon + 1;   /* tm_mon starts at zero */
	day = time->tm_mday;
	hrs = time->tm_hour;
	min = time->tm_min;
	sec = time->tm_sec;

	if (yrs > 255)	/* They are unsigned */
		return -EINVAL;

	spin_lock_irqsave(&rtc_lock, flags);
#ifdef CONFIG_MACH_DECSTATION
	real_yrs = yrs;
	leap_yr = ((!((yrs + 1900) % 4) && ((yrs + 1900) % 100)) ||
			!((yrs + 1900) % 400));
	yrs = 72;

	/*
	 * We want to keep the year set to 73 until March
	 * for non-leap years, so that Feb, 29th is handled
	 * correctly.
	 */
	if (!leap_yr && mon < 3) {
		real_yrs--;
		yrs = 73;
	}
#endif

#ifdef CONFIG_ACPI
	if (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century) {
		century = (yrs + 1900) / 100;
		yrs %= 100;
	}
#endif

	/* These limits and adjustments are independent of
	 * whether the chip is in binary mode or not.
	 */
	if (yrs > 169) {
		spin_unlock_irqrestore(&rtc_lock, flags);
		return -EINVAL;
	}

	if (yrs >= 100)
		yrs -= 100;

	if (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY)
	    || RTC_ALWAYS_BCD) {
		sec = bin2bcd(sec);
		min = bin2bcd(min);
		hrs = bin2bcd(hrs);
		day = bin2bcd(day);
		mon = bin2bcd(mon);
		yrs = bin2bcd(yrs);
		century = bin2bcd(century);
	}

	save_control = CMOS_READ(RTC_CONTROL);
	CMOS_WRITE((save_control|RTC_SET), RTC_CONTROL);
	save_freq_select = CMOS_READ(RTC_FREQ_SELECT);
	CMOS_WRITE((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

#ifdef CONFIG_MACH_DECSTATION
	CMOS_WRITE(real_yrs, RTC_DEC_YEAR);
#endif
	CMOS_WRITE(yrs, RTC_YEAR);
	CMOS_WRITE(mon, RTC_MONTH);
	CMOS_WRITE(day, RTC_DAY_OF_MONTH);
	CMOS_WRITE(hrs, RTC_HOURS);
	CMOS_WRITE(min, RTC_MINUTES);
	CMOS_WRITE(sec, RTC_SECONDS);
#ifdef CONFIG_ACPI
	if (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century)
		CMOS_WRITE(century, acpi_gbl_FADT.century);
#endif

	CMOS_WRITE(save_control, RTC_CONTROL);
	CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);

	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}