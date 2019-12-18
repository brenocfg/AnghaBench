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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int PGTYPESdate_dayofweek (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGTYPESdate_from_timestamp (int /*<<< orphan*/ ) ; 
 int dttofmtasc_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct tm*,char*,int*,char const*) ; 
 int /*<<< orphan*/  timestamp2tm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
PGTYPEStimestamp_fmt_asc(timestamp * ts, char *output, int str_len, const char *fmtstr)
{
	struct tm	tm;
	fsec_t		fsec;
	date		dDate;
	int			dow;

	dDate = PGTYPESdate_from_timestamp(*ts);
	dow = PGTYPESdate_dayofweek(dDate);
	timestamp2tm(*ts, NULL, &tm, &fsec, NULL);

	return dttofmtasc_replace(ts, dDate, dow, &tm, output, &str_len, fmtstr);
}