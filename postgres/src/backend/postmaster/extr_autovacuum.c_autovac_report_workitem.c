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
typedef  int /*<<< orphan*/  blk ;
struct TYPE_3__ {int avw_type; int avw_blockNumber; } ;
typedef  TYPE_1__ AutoVacuumWorkItem ;

/* Variables and functions */
#define  AVW_BRINSummarizeRange 128 
 scalar_t__ BlockNumberIsValid (int) ; 
 int MAX_AUTOVAC_ACTIV_LEN ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  SetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
autovac_report_workitem(AutoVacuumWorkItem *workitem,
						const char *nspname, const char *relname)
{
	char		activity[MAX_AUTOVAC_ACTIV_LEN + 12 + 2];
	char		blk[12 + 2];
	int			len;

	switch (workitem->avw_type)
	{
		case AVW_BRINSummarizeRange:
			snprintf(activity, MAX_AUTOVAC_ACTIV_LEN,
					 "autovacuum: BRIN summarize");
			break;
	}

	/*
	 * Report the qualified name of the relation, and the block number if any
	 */
	len = strlen(activity);

	if (BlockNumberIsValid(workitem->avw_blockNumber))
		snprintf(blk, sizeof(blk), " %u", workitem->avw_blockNumber);
	else
		blk[0] = '\0';

	snprintf(activity + len, MAX_AUTOVAC_ACTIV_LEN - len,
			 " %s.%s%s", nspname, relname, blk);

	/* Set statement_timestamp() to current time for pg_stat_activity */
	SetCurrentStatementStartTimestamp();

	pgstat_report_activity(STATE_RUNNING, activity);
}