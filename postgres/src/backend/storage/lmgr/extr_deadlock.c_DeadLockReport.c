#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  locktag_lockmethodid; } ;
struct TYPE_13__ {int pid; int /*<<< orphan*/  lockmode; TYPE_10__ locktag; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ DEADLOCK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DescribeLockTag (TYPE_1__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ERRCODE_T_R_DEADLOCK_DETECTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetLockmodeName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 TYPE_2__* deadlockDetails ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_log (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int nDeadlockDetails ; 
 int /*<<< orphan*/  pgstat_get_backend_current_activity (int,int) ; 
 int /*<<< orphan*/  pgstat_report_deadlock () ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

void
DeadLockReport(void)
{
	StringInfoData clientbuf;	/* errdetail for client */
	StringInfoData logbuf;		/* errdetail for server log */
	StringInfoData locktagbuf;
	int			i;

	initStringInfo(&clientbuf);
	initStringInfo(&logbuf);
	initStringInfo(&locktagbuf);

	/* Generate the "waits for" lines sent to the client */
	for (i = 0; i < nDeadlockDetails; i++)
	{
		DEADLOCK_INFO *info = &deadlockDetails[i];
		int			nextpid;

		/* The last proc waits for the first one... */
		if (i < nDeadlockDetails - 1)
			nextpid = info[1].pid;
		else
			nextpid = deadlockDetails[0].pid;

		/* reset locktagbuf to hold next object description */
		resetStringInfo(&locktagbuf);

		DescribeLockTag(&locktagbuf, &info->locktag);

		if (i > 0)
			appendStringInfoChar(&clientbuf, '\n');

		appendStringInfo(&clientbuf,
						 _("Process %d waits for %s on %s; blocked by process %d."),
						 info->pid,
						 GetLockmodeName(info->locktag.locktag_lockmethodid,
										 info->lockmode),
						 locktagbuf.data,
						 nextpid);
	}

	/* Duplicate all the above for the server ... */
	appendBinaryStringInfo(&logbuf, clientbuf.data, clientbuf.len);

	/* ... and add info about query strings */
	for (i = 0; i < nDeadlockDetails; i++)
	{
		DEADLOCK_INFO *info = &deadlockDetails[i];

		appendStringInfoChar(&logbuf, '\n');

		appendStringInfo(&logbuf,
						 _("Process %d: %s"),
						 info->pid,
						 pgstat_get_backend_current_activity(info->pid, false));
	}

	pgstat_report_deadlock();

	ereport(ERROR,
			(errcode(ERRCODE_T_R_DEADLOCK_DETECTED),
			 errmsg("deadlock detected"),
			 errdetail_internal("%s", clientbuf.data),
			 errdetail_log("%s", logbuf.data),
			 errhint("See server log for query details.")));
}