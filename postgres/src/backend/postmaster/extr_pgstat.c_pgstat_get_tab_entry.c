#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tables; } ;
struct TYPE_5__ {scalar_t__ autovac_analyze_count; scalar_t__ autovac_analyze_timestamp; scalar_t__ analyze_count; scalar_t__ analyze_timestamp; scalar_t__ autovac_vacuum_count; scalar_t__ autovac_vacuum_timestamp; scalar_t__ vacuum_count; scalar_t__ vacuum_timestamp; scalar_t__ blocks_hit; scalar_t__ blocks_fetched; scalar_t__ changes_since_analyze; scalar_t__ n_dead_tuples; scalar_t__ n_live_tuples; scalar_t__ tuples_hot_updated; scalar_t__ tuples_deleted; scalar_t__ tuples_updated; scalar_t__ tuples_inserted; scalar_t__ tuples_fetched; scalar_t__ tuples_returned; scalar_t__ numscans; } ;
typedef  TYPE_1__ PgStat_StatTabEntry ;
typedef  TYPE_2__ PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HASHACTION ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static PgStat_StatTabEntry *
pgstat_get_tab_entry(PgStat_StatDBEntry *dbentry, Oid tableoid, bool create)
{
	PgStat_StatTabEntry *result;
	bool		found;
	HASHACTION	action = (create ? HASH_ENTER : HASH_FIND);

	/* Lookup or create the hash table entry for this table */
	result = (PgStat_StatTabEntry *) hash_search(dbentry->tables,
												 &tableoid,
												 action, &found);

	if (!create && !found)
		return NULL;

	/* If not found, initialize the new one. */
	if (!found)
	{
		result->numscans = 0;
		result->tuples_returned = 0;
		result->tuples_fetched = 0;
		result->tuples_inserted = 0;
		result->tuples_updated = 0;
		result->tuples_deleted = 0;
		result->tuples_hot_updated = 0;
		result->n_live_tuples = 0;
		result->n_dead_tuples = 0;
		result->changes_since_analyze = 0;
		result->blocks_fetched = 0;
		result->blocks_hit = 0;
		result->vacuum_timestamp = 0;
		result->vacuum_count = 0;
		result->autovac_vacuum_timestamp = 0;
		result->autovac_vacuum_count = 0;
		result->analyze_timestamp = 0;
		result->analyze_count = 0;
		result->autovac_analyze_timestamp = 0;
		result->autovac_analyze_count = 0;
	}

	return result;
}