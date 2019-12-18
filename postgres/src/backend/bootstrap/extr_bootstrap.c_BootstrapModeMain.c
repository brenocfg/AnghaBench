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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InitPostgres (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InitProcess () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int MAXATTR ; 
 int* Nulls ; 
 int /*<<< orphan*/  RelationMapFinishBootstrap () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/ ** attrtypes ; 
 int /*<<< orphan*/  boot_yyparse () ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pg_link_canary_is_frontend () ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
BootstrapModeMain(void)
{
	int			i;

	Assert(!IsUnderPostmaster);
	Assert(IsBootstrapProcessingMode());

	/*
	 * To ensure that src/common/link-canary.c is linked into the backend, we
	 * must call it from somewhere.  Here is as good as anywhere.
	 */
	if (pg_link_canary_is_frontend())
		elog(ERROR, "backend is incorrectly linked to frontend functions");

	/*
	 * Do backend-like initialization for bootstrap mode
	 */
	InitProcess();

	InitPostgres(NULL, InvalidOid, NULL, InvalidOid, NULL, false);

	/* Initialize stuff for bootstrap-file processing */
	for (i = 0; i < MAXATTR; i++)
	{
		attrtypes[i] = NULL;
		Nulls[i] = false;
	}

	/*
	 * Process bootstrap input.
	 */
	StartTransactionCommand();
	boot_yyparse();
	CommitTransactionCommand();

	/*
	 * We should now know about all mapped relations, so it's okay to write
	 * out the initial relation mapping files.
	 */
	RelationMapFinishBootstrap();

	/* Clean up and exit */
	cleanup();
	proc_exit(0);
}