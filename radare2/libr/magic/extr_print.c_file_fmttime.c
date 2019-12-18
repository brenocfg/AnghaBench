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
typedef  scalar_t__ ut32 ;
typedef  scalar_t__ time_t ;
struct tm {int tm_isdst; } ;

/* Variables and functions */
 char* asctime (struct tm*) ; 
 char* ctime (scalar_t__*) ; 
 struct tm* gmtime_r (scalar_t__*,struct tm*) ; 
 struct tm* localtime (scalar_t__*) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

const char *file_fmttime(ut32 v, int local) {
	char *pp;
	time_t t = (time_t)v;
	struct tm *tm;
	struct tm timestruct;

	if (local) {
		pp = ctime(&t);
	} else {
#ifndef HAVE_DAYLIGHT
		static int daylight = 0;
#ifdef HAVE_TM_ISDST
		static time_t now = (time_t)0;

		if (now == (time_t)0) {
			struct tm *tm1;
			(void)time(&now);
			tm1 = localtime(&now);
			if (!tm1)
				return "*Invalid time*";
			daylight = tm1->tm_isdst;
		}
#endif /* HAVE_TM_ISDST */
#endif /* HAVE_DAYLIGHT */
		if (daylight)
			t += 3600;
		tm = gmtime_r(&t, &timestruct);
		if (!tm)
			return "*Invalid time*";
		pp = asctime (tm);
	}

	pp[strcspn (pp, "\n")] = '\0';
	return pp;
}