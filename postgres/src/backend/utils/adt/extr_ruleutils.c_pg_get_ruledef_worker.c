#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_5__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_OK_CONNECT ; 
 scalar_t__ SPI_OK_FINISH ; 
 int SPI_OK_SELECT ; 
 scalar_t__ SPI_connect () ; 
 int SPI_execute_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_finish () ; 
 int /*<<< orphan*/  SPI_keepplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_prepare (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int SPI_processed ; 
 TYPE_4__* SPI_tuptable ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  make_ruledef (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * plan_getrulebyoid ; 
 int /*<<< orphan*/  query_getrulebyoid ; 

__attribute__((used)) static char *
pg_get_ruledef_worker(Oid ruleoid, int prettyFlags)
{
	Datum		args[1];
	char		nulls[1];
	int			spirc;
	HeapTuple	ruletup;
	TupleDesc	rulettc;
	StringInfoData buf;

	/*
	 * Do this first so that string is alloc'd in outer context not SPI's.
	 */
	initStringInfo(&buf);

	/*
	 * Connect to SPI manager
	 */
	if (SPI_connect() != SPI_OK_CONNECT)
		elog(ERROR, "SPI_connect failed");

	/*
	 * On the first call prepare the plan to lookup pg_rewrite. We read
	 * pg_rewrite over the SPI manager instead of using the syscache to be
	 * checked for read access on pg_rewrite.
	 */
	if (plan_getrulebyoid == NULL)
	{
		Oid			argtypes[1];
		SPIPlanPtr	plan;

		argtypes[0] = OIDOID;
		plan = SPI_prepare(query_getrulebyoid, 1, argtypes);
		if (plan == NULL)
			elog(ERROR, "SPI_prepare failed for \"%s\"", query_getrulebyoid);
		SPI_keepplan(plan);
		plan_getrulebyoid = plan;
	}

	/*
	 * Get the pg_rewrite tuple for this rule
	 */
	args[0] = ObjectIdGetDatum(ruleoid);
	nulls[0] = ' ';
	spirc = SPI_execute_plan(plan_getrulebyoid, args, nulls, true, 0);
	if (spirc != SPI_OK_SELECT)
		elog(ERROR, "failed to get pg_rewrite tuple for rule %u", ruleoid);
	if (SPI_processed != 1)
	{
		/*
		 * There is no tuple data available here, just keep the output buffer
		 * empty.
		 */
	}
	else
	{
		/*
		 * Get the rule's definition and put it into executor's memory
		 */
		ruletup = SPI_tuptable->vals[0];
		rulettc = SPI_tuptable->tupdesc;
		make_ruledef(&buf, ruletup, rulettc, prettyFlags);
	}

	/*
	 * Disconnect from SPI manager
	 */
	if (SPI_finish() != SPI_OK_FINISH)
		elog(ERROR, "SPI_finish failed");

	if (buf.len == 0)
		return NULL;

	return buf.data;
}