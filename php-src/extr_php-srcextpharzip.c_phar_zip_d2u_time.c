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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int PHAR_GET_16 (char*) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 struct tm* php_localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static time_t phar_zip_d2u_time(char *cdtime, char *cddate) /* {{{ */
{
	int dtime = PHAR_GET_16(cdtime), ddate = PHAR_GET_16(cddate);
	struct tm *tm, tmbuf;
	time_t now;

	now = time(NULL);
	tm = php_localtime_r(&now, &tmbuf);

	tm->tm_year = ((ddate>>9)&127) + 1980 - 1900;
	tm->tm_mon = ((ddate>>5)&15) - 1;
	tm->tm_mday = ddate&31;

	tm->tm_hour = (dtime>>11)&31;
	tm->tm_min = (dtime>>5)&63;
	tm->tm_sec = (dtime<<1)&62;

	return mktime(tm);
}