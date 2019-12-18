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
struct TYPE_7__ {int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_6__ {int /*<<< orphan*/ * functions; int /*<<< orphan*/ * tables; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgResetcounter ;

/* Variables and functions */
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_dbentry_counters (TYPE_1__*) ; 

__attribute__((used)) static void
pgstat_recv_resetcounter(PgStat_MsgResetcounter *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	/*
	 * Lookup the database in the hashtable.  Nothing to do if not there.
	 */
	dbentry = pgstat_get_db_entry(msg->m_databaseid, false);

	if (!dbentry)
		return;

	/*
	 * We simply throw away all the database's table entries by recreating a
	 * new hash table for them.
	 */
	if (dbentry->tables != NULL)
		hash_destroy(dbentry->tables);
	if (dbentry->functions != NULL)
		hash_destroy(dbentry->functions);

	dbentry->tables = NULL;
	dbentry->functions = NULL;

	/*
	 * Reset database-level stats, too.  This creates empty hash tables for
	 * tables and functions.
	 */
	reset_dbentry_counters(dbentry);
}