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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHAR_SET_16 (char*,int) ; 
 struct tm* php_localtime_r (int /*<<< orphan*/ *,struct tm*) ; 

__attribute__((used)) static void phar_zip_u2d_time(time_t time, char *dtime, char *ddate) /* {{{ */
{
	uint16_t ctime, cdate;
	struct tm *tm, tmbuf;

	tm = php_localtime_r(&time, &tmbuf);
	if (tm->tm_year >= 1980) {
		cdate = ((tm->tm_year+1900-1980)<<9) + ((tm->tm_mon+1)<<5) + tm->tm_mday;
		ctime = ((tm->tm_hour)<<11) + ((tm->tm_min)<<5) + ((tm->tm_sec)>>1);
	} else {
		/* This is the earliest date/time supported by zip. */
		cdate = (1<<5) + 1; /* 1980-01-01 */
		ctime = 0; /* 00:00:00 */
	}

	PHAR_SET_16(dtime, ctime);
	PHAR_SET_16(ddate, cdate);
}