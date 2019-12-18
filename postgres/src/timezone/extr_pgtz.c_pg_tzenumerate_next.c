#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  TZname; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {size_t depth; char** dirname; int baselen; TYPE_2__ tz; int /*<<< orphan*/ * dirdesc; } ;
typedef  TYPE_1__ pg_tzenum ;
typedef  TYPE_2__ pg_tz ;
typedef  int /*<<< orphan*/  fullname ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDir (char*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int MAX_TZDIR_DEPTH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_tz_acceptable (TYPE_2__*) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tzload (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

pg_tz *
pg_tzenumerate_next(pg_tzenum *dir)
{
	while (dir->depth >= 0)
	{
		struct dirent *direntry;
		char		fullname[MAXPGPATH * 2];
		struct stat statbuf;

		direntry = ReadDir(dir->dirdesc[dir->depth], dir->dirname[dir->depth]);

		if (!direntry)
		{
			/* End of this directory */
			FreeDir(dir->dirdesc[dir->depth]);
			pfree(dir->dirname[dir->depth]);
			dir->depth--;
			continue;
		}

		if (direntry->d_name[0] == '.')
			continue;

		snprintf(fullname, sizeof(fullname), "%s/%s",
				 dir->dirname[dir->depth], direntry->d_name);
		if (stat(fullname, &statbuf) != 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not stat \"%s\": %m", fullname)));

		if (S_ISDIR(statbuf.st_mode))
		{
			/* Step into the subdirectory */
			if (dir->depth >= MAX_TZDIR_DEPTH - 1)
				ereport(ERROR,
						(errmsg_internal("timezone directory stack overflow")));
			dir->depth++;
			dir->dirname[dir->depth] = pstrdup(fullname);
			dir->dirdesc[dir->depth] = AllocateDir(fullname);
			if (!dir->dirdesc[dir->depth])
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open directory \"%s\": %m",
								fullname)));

			/* Start over reading in the new directory */
			continue;
		}

		/*
		 * Load this timezone using tzload() not pg_tzset(), so we don't fill
		 * the cache.  Also, don't ask for the canonical spelling: we already
		 * know it, and pg_open_tzfile's way of finding it out is pretty
		 * inefficient.
		 */
		if (tzload(fullname + dir->baselen, NULL, &dir->tz.state, true) != 0)
		{
			/* Zone could not be loaded, ignore it */
			continue;
		}

		if (!pg_tz_acceptable(&dir->tz))
		{
			/* Ignore leap-second zones */
			continue;
		}

		/* OK, return the canonical zone name spelling. */
		strlcpy(dir->tz.TZname, fullname + dir->baselen,
				sizeof(dir->tz.TZname));

		/* Timezone loaded OK. */
		return &dir->tz;
	}

	/* Nothing more found */
	return NULL;
}