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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  interval ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeInterval (struct tm*,int /*<<< orphan*/ ,int,char*) ; 
 int INTSTYLE_POSTGRES_VERBOSE ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 int /*<<< orphan*/  PGTYPES_INTVL_BAD_INTERVAL ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ interval2tm (int /*<<< orphan*/ ,struct tm*,int /*<<< orphan*/ *) ; 
 char* pgtypes_strdup (char*) ; 

char *
PGTYPESinterval_to_asc(interval * span)
{
	struct tm	tt,
			   *tm = &tt;
	fsec_t		fsec;
	char		buf[MAXDATELEN + 1];
	int			IntervalStyle = INTSTYLE_POSTGRES_VERBOSE;

	if (interval2tm(*span, tm, &fsec) != 0)
	{
		errno = PGTYPES_INTVL_BAD_INTERVAL;
		return NULL;
	}

	EncodeInterval(tm, fsec, IntervalStyle, buf);

	return pgtypes_strdup(buf);
}