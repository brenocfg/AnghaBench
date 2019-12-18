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
typedef  int /*<<< orphan*/  time64_t ;
struct tm {long tm_hour; long tm_min; long tm_sec; int tm_wday; long tm_year; long tm_yday; long tm_mon; long tm_mday; } ;

/* Variables and functions */
 long SECS_PER_DAY ; 
 long SECS_PER_HOUR ; 
 size_t __isleap (long) ; 
 unsigned short** __mon_yday ; 
 long div_s64_rem (int /*<<< orphan*/ ,long,int*) ; 
 scalar_t__ leaps_between (long,long) ; 
 long math_div (long,int) ; 

void time64_to_tm(time64_t totalsecs, int offset, struct tm *result)
{
	long days, rem, y;
	int remainder;
	const unsigned short *ip;

	days = div_s64_rem(totalsecs, SECS_PER_DAY, &remainder);
	rem = remainder;
	rem += offset;
	while (rem < 0) {
		rem += SECS_PER_DAY;
		--days;
	}
	while (rem >= SECS_PER_DAY) {
		rem -= SECS_PER_DAY;
		++days;
	}

	result->tm_hour = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	result->tm_min = rem / 60;
	result->tm_sec = rem % 60;

	/* January 1, 1970 was a Thursday. */
	result->tm_wday = (4 + days) % 7;
	if (result->tm_wday < 0)
		result->tm_wday += 7;

	y = 1970;

	while (days < 0 || days >= (__isleap(y) ? 366 : 365)) {
		/* Guess a corrected year, assuming 365 days per year. */
		long yg = y + math_div(days, 365);

		/* Adjust DAYS and Y to match the guessed year. */
		days -= (yg - y) * 365 + leaps_between(y, yg);
		y = yg;
	}

	result->tm_year = y - 1900;

	result->tm_yday = days;

	ip = __mon_yday[__isleap(y)];
	for (y = 11; days < ip[y]; y--)
		continue;
	days -= ip[y];

	result->tm_mon = y;
	result->tm_mday = days + 1;
}