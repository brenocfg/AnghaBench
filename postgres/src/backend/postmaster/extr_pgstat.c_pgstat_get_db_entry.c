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
typedef  int /*<<< orphan*/  PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HASHACTION ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pgStatDBHash ; 
 int /*<<< orphan*/  reset_dbentry_counters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PgStat_StatDBEntry *
pgstat_get_db_entry(Oid databaseid, bool create)
{
	PgStat_StatDBEntry *result;
	bool		found;
	HASHACTION	action = (create ? HASH_ENTER : HASH_FIND);

	/* Lookup or create the hash table entry for this database */
	result = (PgStat_StatDBEntry *) hash_search(pgStatDBHash,
												&databaseid,
												action, &found);

	if (!create && !found)
		return NULL;

	/*
	 * If not found, initialize the new one.  This creates empty hash tables
	 * for tables and functions, too.
	 */
	if (!found)
		reset_dbentry_counters(result);

	return result;
}