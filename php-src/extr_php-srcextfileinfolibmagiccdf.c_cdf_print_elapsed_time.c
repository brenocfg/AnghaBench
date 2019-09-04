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
typedef  int cdf_timestamp_t ;

/* Variables and functions */
 int CDF_TIME_PREC ; 
 scalar_t__ snprintf (char*,size_t,char*,int) ; 

int
cdf_print_elapsed_time(char *buf, size_t bufsiz, cdf_timestamp_t ts)
{
	int len = 0;
	int days, hours, mins, secs;

	ts /= CDF_TIME_PREC;
	secs = (int)(ts % 60);
	ts /= 60;
	mins = (int)(ts % 60);
	ts /= 60;
	hours = (int)(ts % 24);
	ts /= 24;
	days = (int)ts;

	if (days) {
		len += snprintf(buf + len, bufsiz - len, "%dd+", days);
		if ((size_t)len >= bufsiz)
			return len;
	}

	if (days || hours) {
		len += snprintf(buf + len, bufsiz - len, "%.2d:", hours);
		if ((size_t)len >= bufsiz)
			return len;
	}

	len += snprintf(buf + len, bufsiz - len, "%.2d:", mins);
	if ((size_t)len >= bufsiz)
		return len;

	len += snprintf(buf + len, bufsiz - len, "%.2d", secs);
	return len;
}