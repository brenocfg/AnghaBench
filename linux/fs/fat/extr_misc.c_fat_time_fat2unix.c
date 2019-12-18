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
typedef  int u16 ;
typedef  int time64_t ;
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct msdos_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ DAYS_DELTA ; 
 scalar_t__ IS_LEAP_YEAR (long) ; 
 int SECS_PER_DAY ; 
 int SECS_PER_HOUR ; 
 int SECS_PER_MIN ; 
 long YEAR_2100 ; 
 scalar_t__* days_in_year ; 
 scalar_t__ fat_tz_offset (struct msdos_sb_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

void fat_time_fat2unix(struct msdos_sb_info *sbi, struct timespec64 *ts,
		       __le16 __time, __le16 __date, u8 time_cs)
{
	u16 time = le16_to_cpu(__time), date = le16_to_cpu(__date);
	time64_t second;
	long day, leap_day, month, year;

	year  = date >> 9;
	month = max(1, (date >> 5) & 0xf);
	day   = max(1, date & 0x1f) - 1;

	leap_day = (year + 3) / 4;
	if (year > YEAR_2100)		/* 2100 isn't leap year */
		leap_day--;
	if (IS_LEAP_YEAR(year) && month > 2)
		leap_day++;

	second =  (time & 0x1f) << 1;
	second += ((time >> 5) & 0x3f) * SECS_PER_MIN;
	second += (time >> 11) * SECS_PER_HOUR;
	second += (time64_t)(year * 365 + leap_day
		   + days_in_year[month] + day
		   + DAYS_DELTA) * SECS_PER_DAY;

	second += fat_tz_offset(sbi);

	if (time_cs) {
		ts->tv_sec = second + (time_cs / 100);
		ts->tv_nsec = (time_cs % 100) * 10000000;
	} else {
		ts->tv_sec = second;
		ts->tv_nsec = 0;
	}
}