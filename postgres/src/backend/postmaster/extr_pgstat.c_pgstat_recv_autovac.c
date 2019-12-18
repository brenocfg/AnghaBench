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
struct TYPE_6__ {int /*<<< orphan*/  m_start_time; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_autovac_time; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgAutovacStart ;

/* Variables and functions */
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_autovac(PgStat_MsgAutovacStart *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	/*
	 * Store the last autovacuum time in the database's hashtable entry.
	 */
	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);

	dbentry->last_autovac_time = msg->m_start_time;
}