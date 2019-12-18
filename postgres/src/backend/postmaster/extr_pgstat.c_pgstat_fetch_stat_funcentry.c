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
struct TYPE_3__ {int /*<<< orphan*/ * functions; } ;
typedef  int /*<<< orphan*/  PgStat_StatFuncEntry ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  backend_read_statsfile () ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pgstat_fetch_stat_dbentry (int /*<<< orphan*/ ) ; 

PgStat_StatFuncEntry *
pgstat_fetch_stat_funcentry(Oid func_id)
{
	PgStat_StatDBEntry *dbentry;
	PgStat_StatFuncEntry *funcentry = NULL;

	/* load the stats file if needed */
	backend_read_statsfile();

	/* Lookup our database, then find the requested function.  */
	dbentry = pgstat_fetch_stat_dbentry(MyDatabaseId);
	if (dbentry != NULL && dbentry->functions != NULL)
	{
		funcentry = (PgStat_StatFuncEntry *) hash_search(dbentry->functions,
														 (void *) &func_id,
														 HASH_FIND, NULL);
	}

	return funcentry;
}