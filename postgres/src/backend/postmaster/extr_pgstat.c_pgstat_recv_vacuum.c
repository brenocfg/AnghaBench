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
struct TYPE_6__ {int /*<<< orphan*/  m_vacuumtime; scalar_t__ m_autovacuum; int /*<<< orphan*/  m_dead_tuples; int /*<<< orphan*/  m_live_tuples; int /*<<< orphan*/  m_tableoid; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  vacuum_count; int /*<<< orphan*/  vacuum_timestamp; int /*<<< orphan*/  autovac_vacuum_count; int /*<<< orphan*/  autovac_vacuum_timestamp; int /*<<< orphan*/  n_dead_tuples; int /*<<< orphan*/  n_live_tuples; } ;
typedef  TYPE_1__ PgStat_StatTabEntry ;
typedef  int /*<<< orphan*/  PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgVacuum ;

/* Variables and functions */
 int /*<<< orphan*/ * pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pgstat_get_tab_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_vacuum(PgStat_MsgVacuum *msg, int len)
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

	if (msg->m_autovacuum)
	{
		tabentry->autovac_vacuum_timestamp = msg->m_vacuumtime;
		tabentry->autovac_vacuum_count++;
	}
	else
	{
		tabentry->vacuum_timestamp = msg->m_vacuumtime;
		tabentry->vacuum_count++;
	}
}