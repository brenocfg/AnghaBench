#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  int time64_t ;
struct timespec64 {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int Day; int Month; int Year; } ;
struct TYPE_3__ {int TwoSeconds; int Minutes; int Hours; } ;
typedef  TYPE_1__ SMB_TIME ;
typedef  TYPE_2__ SMB_DATE ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int clamp (int,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int* total_days_of_prev_months ; 

struct timespec64 cnvrtDosUnixTm(__le16 le_date, __le16 le_time, int offset)
{
	struct timespec64 ts;
	time64_t sec, days;
	int min, day, month, year;
	u16 date = le16_to_cpu(le_date);
	u16 time = le16_to_cpu(le_time);
	SMB_TIME *st = (SMB_TIME *)&time;
	SMB_DATE *sd = (SMB_DATE *)&date;

	cifs_dbg(FYI, "date %d time %d\n", date, time);

	sec = 2 * st->TwoSeconds;
	min = st->Minutes;
	if ((sec > 59) || (min > 59))
		cifs_dbg(VFS, "illegal time min %d sec %lld\n", min, sec);
	sec += (min * 60);
	sec += 60 * 60 * st->Hours;
	if (st->Hours > 24)
		cifs_dbg(VFS, "illegal hours %d\n", st->Hours);
	day = sd->Day;
	month = sd->Month;
	if (day < 1 || day > 31 || month < 1 || month > 12) {
		cifs_dbg(VFS, "illegal date, month %d day: %d\n", month, day);
		day = clamp(day, 1, 31);
		month = clamp(month, 1, 12);
	}
	month -= 1;
	days = day + total_days_of_prev_months[month];
	days += 3652; /* account for difference in days between 1980 and 1970 */
	year = sd->Year;
	days += year * 365;
	days += (year/4); /* leap year */
	/* generalized leap year calculation is more complex, ie no leap year
	for years/100 except for years/400, but since the maximum number for DOS
	 year is 2**7, the last year is 1980+127, which means we need only
	 consider 2 special case years, ie the years 2000 and 2100, and only
	 adjust for the lack of leap year for the year 2100, as 2000 was a
	 leap year (divisable by 400) */
	if (year >= 120)  /* the year 2100 */
		days = days - 1;  /* do not count leap year for the year 2100 */

	/* adjust for leap year where we are still before leap day */
	if (year != 120)
		days -= ((year & 0x03) == 0) && (month < 2 ? 1 : 0);
	sec += 24 * 60 * 60 * days;

	ts.tv_sec = sec + offset;

	/* cifs_dbg(FYI, "sec after cnvrt dos to unix time %d\n",sec); */

	ts.tv_nsec = 0;
	return ts;
}