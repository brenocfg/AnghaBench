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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
struct timespec {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST (int /*<<< orphan*/ ,scalar_t__) ; 
 int FILE_T_LOCAL ; 
 int FILE_T_WINDOWS ; 
 int /*<<< orphan*/  cdf_timestamp_t ; 
 int /*<<< orphan*/  cdf_timestamp_to_timespec (struct timespec*,int /*<<< orphan*/ ) ; 
 char* php_asctime_r (struct tm*,char*) ; 
 struct tm* php_gmtime_r (scalar_t__*,struct tm*) ; 
 struct tm* php_localtime_r (scalar_t__*,struct tm*) ; 
 char const* strcpy (char*,char*) ; 
 size_t strcspn (char*,char*) ; 

const char *
file_fmttime(uint64_t v, int flags, char *buf)
{
	char *pp;
	time_t t;
	struct tm *tm, tmz;

	if (flags & FILE_T_WINDOWS) {
		struct timespec ts;
		cdf_timestamp_to_timespec(&ts, CAST(cdf_timestamp_t, v));
		t = ts.tv_sec;
	} else {
		// XXX: perhaps detect and print something if overflow
		// on 32 bit time_t?
		t = (time_t)v;
	}

	if (flags & FILE_T_LOCAL) {
		tm = php_localtime_r(&t, &tmz);
	} else {
		tm = php_gmtime_r(&t, &tmz);
	}
	if (tm == NULL)
		goto out;
	pp = php_asctime_r(tm, buf);

	if (pp == NULL)
		goto out;
	pp[strcspn(pp, "\n")] = '\0';
	return pp;
out:
	return strcpy(buf, "*Invalid time*");
}