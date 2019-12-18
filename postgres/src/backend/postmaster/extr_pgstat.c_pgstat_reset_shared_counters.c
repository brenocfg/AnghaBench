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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {int /*<<< orphan*/  m_hdr; int /*<<< orphan*/  m_resettarget; } ;
typedef  TYPE_1__ PgStat_MsgResetsharedcounter ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PGSTAT_MTYPE_RESETSHAREDCOUNTER ; 
 int /*<<< orphan*/  RESET_ARCHIVER ; 
 int /*<<< orphan*/  RESET_BGWRITER ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ pgStatSock ; 
 int /*<<< orphan*/  pgstat_send (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pgstat_setheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
pgstat_reset_shared_counters(const char *target)
{
	PgStat_MsgResetsharedcounter msg;

	if (pgStatSock == PGINVALID_SOCKET)
		return;

	if (strcmp(target, "archiver") == 0)
		msg.m_resettarget = RESET_ARCHIVER;
	else if (strcmp(target, "bgwriter") == 0)
		msg.m_resettarget = RESET_BGWRITER;
	else
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("unrecognized reset target: \"%s\"", target),
				 errhint("Target must be \"archiver\" or \"bgwriter\".")));

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_RESETSHAREDCOUNTER);
	pgstat_send(&msg, sizeof(msg));
}