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
typedef  int uint32 ;
struct TYPE_3__ {int bgw_flags; } ;
typedef  TYPE_1__ BackgroundWorker ;

/* Variables and functions */
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_BYPASS_ALLOWCONN ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  InitPostgres (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsInitProcessingMode () ; 
 TYPE_1__* MyBgworkerEntry ; 
 int /*<<< orphan*/  NormalProcessing ; 
 int /*<<< orphan*/  SetProcessingMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
BackgroundWorkerInitializeConnection(const char *dbname, const char *username, uint32 flags)
{
	BackgroundWorker *worker = MyBgworkerEntry;

	/* XXX is this the right errcode? */
	if (!(worker->bgw_flags & BGWORKER_BACKEND_DATABASE_CONNECTION))
		ereport(FATAL,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("database connection requirement not indicated during registration")));

	InitPostgres(dbname, InvalidOid, username, InvalidOid, NULL, (flags & BGWORKER_BYPASS_ALLOWCONN) != 0);

	/* it had better not gotten out of "init" mode yet */
	if (!IsInitProcessingMode())
		ereport(ERROR,
				(errmsg("invalid processing mode in background worker")));
	SetProcessingMode(NormalProcessing);
}