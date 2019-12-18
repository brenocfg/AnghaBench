#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_2__ {int from_sql; int /*<<< orphan*/  prepare_time; int /*<<< orphan*/ * plansource; } ;
typedef  TYPE_1__ PreparedStatement ;
typedef  int /*<<< orphan*/  CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_PSTATEMENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  InitQueryHashTable () ; 
 int /*<<< orphan*/  SaveCachedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  prepared_queries ; 

void
StorePreparedStatement(const char *stmt_name,
					   CachedPlanSource *plansource,
					   bool from_sql)
{
	PreparedStatement *entry;
	TimestampTz cur_ts = GetCurrentStatementStartTimestamp();
	bool		found;

	/* Initialize the hash table, if necessary */
	if (!prepared_queries)
		InitQueryHashTable();

	/* Add entry to hash table */
	entry = (PreparedStatement *) hash_search(prepared_queries,
											  stmt_name,
											  HASH_ENTER,
											  &found);

	/* Shouldn't get a duplicate entry */
	if (found)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_PSTATEMENT),
				 errmsg("prepared statement \"%s\" already exists",
						stmt_name)));

	/* Fill in the hash table entry */
	entry->plansource = plansource;
	entry->from_sql = from_sql;
	entry->prepare_time = cur_ts;

	/* Now it's safe to move the CachedPlanSource to permanent memory */
	SaveCachedPlan(plansource);
}