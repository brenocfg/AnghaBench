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
struct tztry {int n_test_times; scalar_t__* test_times; } ;
struct tm {scalar_t__ tm_isdst; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct pg_tm {int /*<<< orphan*/ * tm_zone; scalar_t__ tm_isdst; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  scalar_t__ pg_time_t ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int /*<<< orphan*/  TZ_STRLEN_MAX ; 
 int /*<<< orphan*/  compare_tm (struct tm*,struct pg_tm*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pg_load_tz (char const*) ; 
 struct pg_tm* pg_localtime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_tz_acceptable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int
score_timezone(const char *tzname, struct tztry *tt)
{
	int			i;
	pg_time_t	pgtt;
	struct tm  *systm;
	struct pg_tm *pgtm;
	char		cbuf[TZ_STRLEN_MAX + 1];
	pg_tz	   *tz;

	/* Load timezone definition */
	tz = pg_load_tz(tzname);
	if (!tz)
		return -1;				/* unrecognized zone name */

	/* Reject if leap seconds involved */
	if (!pg_tz_acceptable(tz))
	{
#ifdef DEBUG_IDENTIFY_TIMEZONE
		fprintf(stderr, "Reject TZ \"%s\": uses leap seconds\n", tzname);
#endif
		return -1;
	}

	/* Check for match at all the test times */
	for (i = 0; i < tt->n_test_times; i++)
	{
		pgtt = (pg_time_t) (tt->test_times[i]);
		pgtm = pg_localtime(&pgtt, tz);
		if (!pgtm)
			return -1;			/* probably shouldn't happen */
		systm = localtime(&(tt->test_times[i]));
		if (!systm)
		{
#ifdef DEBUG_IDENTIFY_TIMEZONE
			fprintf(stderr, "TZ \"%s\" scores %d: at %ld %04d-%02d-%02d %02d:%02d:%02d %s, system had no data\n",
					tzname, i, (long) pgtt,
					pgtm->tm_year + 1900, pgtm->tm_mon + 1, pgtm->tm_mday,
					pgtm->tm_hour, pgtm->tm_min, pgtm->tm_sec,
					pgtm->tm_isdst ? "dst" : "std");
#endif
			return i;
		}
		if (!compare_tm(systm, pgtm))
		{
#ifdef DEBUG_IDENTIFY_TIMEZONE
			fprintf(stderr, "TZ \"%s\" scores %d: at %ld %04d-%02d-%02d %02d:%02d:%02d %s versus %04d-%02d-%02d %02d:%02d:%02d %s\n",
					tzname, i, (long) pgtt,
					pgtm->tm_year + 1900, pgtm->tm_mon + 1, pgtm->tm_mday,
					pgtm->tm_hour, pgtm->tm_min, pgtm->tm_sec,
					pgtm->tm_isdst ? "dst" : "std",
					systm->tm_year + 1900, systm->tm_mon + 1, systm->tm_mday,
					systm->tm_hour, systm->tm_min, systm->tm_sec,
					systm->tm_isdst ? "dst" : "std");
#endif
			return i;
		}
		if (systm->tm_isdst >= 0)
		{
			/* Check match of zone names, too */
			if (pgtm->tm_zone == NULL)
				return -1;		/* probably shouldn't happen */
			memset(cbuf, 0, sizeof(cbuf));
			strftime(cbuf, sizeof(cbuf) - 1, "%Z", systm);	/* zone abbr */
			if (strcmp(cbuf, pgtm->tm_zone) != 0)
			{
#ifdef DEBUG_IDENTIFY_TIMEZONE
				fprintf(stderr, "TZ \"%s\" scores %d: at %ld \"%s\" versus \"%s\"\n",
						tzname, i, (long) pgtt,
						pgtm->tm_zone, cbuf);
#endif
				return i;
			}
		}
	}

#ifdef DEBUG_IDENTIFY_TIMEZONE
	fprintf(stderr, "TZ \"%s\" gets max score %d\n", tzname, i);
#endif

	return i;
}