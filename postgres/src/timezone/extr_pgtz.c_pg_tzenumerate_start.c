#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** dirname; int /*<<< orphan*/ * dirdesc; scalar_t__ depth; scalar_t__ baselen; } ;
typedef  TYPE_1__ pg_tzenum ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDir (char*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pg_TZDIR () ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

pg_tzenum *
pg_tzenumerate_start(void)
{
	pg_tzenum  *ret = (pg_tzenum *) palloc0(sizeof(pg_tzenum));
	char	   *startdir = pstrdup(pg_TZDIR());

	ret->baselen = strlen(startdir) + 1;
	ret->depth = 0;
	ret->dirname[0] = startdir;
	ret->dirdesc[0] = AllocateDir(startdir);
	if (!ret->dirdesc[0])
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open directory \"%s\": %m", startdir)));
	return ret;
}