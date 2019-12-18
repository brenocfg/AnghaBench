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
typedef  int /*<<< orphan*/  timestamp ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeDateTime (struct tm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EncodeSpecialTimestamp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 int /*<<< orphan*/  PGTYPES_TS_BAD_TIMESTAMP ; 
 scalar_t__ TIMESTAMP_NOT_FINITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* pgtypes_strdup (char*) ; 
 scalar_t__ timestamp2tm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *
PGTYPEStimestamp_to_asc(timestamp tstamp)
{
	struct tm	tt,
			   *tm = &tt;
	char		buf[MAXDATELEN + 1];
	fsec_t		fsec;
	int			DateStyle = 1;	/* this defaults to USE_ISO_DATES, shall we
								 * make it an option? */

	if (TIMESTAMP_NOT_FINITE(tstamp))
		EncodeSpecialTimestamp(tstamp, buf);
	else if (timestamp2tm(tstamp, NULL, tm, &fsec, NULL) == 0)
		EncodeDateTime(tm, fsec, false, 0, NULL, DateStyle, buf, 0);
	else
	{
		errno = PGTYPES_TS_BAD_TIMESTAMP;
		return NULL;
	}
	return pgtypes_strdup(buf);
}