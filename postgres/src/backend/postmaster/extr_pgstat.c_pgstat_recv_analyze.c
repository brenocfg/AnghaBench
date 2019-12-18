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
struct TYPE_6__ {int /*<<< orphan*/  m_analyzetime; scalar_t__ m_autovacuum; scalar_t__ m_resetcounter; int /*<<< orphan*/  m_dead_tuples; int /*<<< orphan*/  m_live_tuples; int /*<<< orphan*/  m_tableoid; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  analyze_count; int /*<<< orphan*/  analyze_timestamp; int /*<<< orphan*/  autovac_analyze_count; int /*<<< orphan*/  autovac_analyze_timestamp; scalar_t__ changes_since_analyze; int /*<<< orphan*/  n_dead_tuples; int /*<<< orphan*/  n_live_tuples; } ;
typedef  TYPE_1__ PgStat_StatTabEntry ;
typedef  int /*<<< orphan*/  PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgAnalyze ;

/* Variables and functions */
 int /*<<< orphan*/ * pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pgstat_get_tab_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_analyze(PgStat_MsgAnalyze *msg, int len)
{
	PgStat_StatDBEntry *dbentry;
	PgStat_StatTabEntry *tabentry;

	/*
	 * Store the data in the table's hashtable entry.
	 */
	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);

	tabentry = pgstat_get_tab_entry(dbentry, msg->m_tableoid, true);

	tabentry->n_live_tuples = msg->m_live_tuples;
	tabentry->n_dead_tuples = msg->m_dead_tuples;

	/*
	 * If commanded, reset changes_since_analyze to zero.  This forgets any
	 * changes that were committed while the ANALYZE was in progress, but we
	 * have no good way to estimate how many of those there were.
	 */
	if (msg->m_resetcounter)
		tabentry->changes_since_analyze = 0;

	if (msg->m_autovacuum)
	{
		tabentry->autovac_analyze_timestamp = msg->m_analyzetime;
		tabentry->autovac_analyze_count++;
	}
	else
	{
		tabentry->analyze_timestamp = msg->m_analyzetime;
		tabentry->analyze_count++;
	}
}