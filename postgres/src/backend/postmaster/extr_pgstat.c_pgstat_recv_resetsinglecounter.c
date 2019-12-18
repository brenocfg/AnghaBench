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
struct TYPE_6__ {scalar_t__ m_resettype; int /*<<< orphan*/  m_objectid; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  functions; int /*<<< orphan*/  tables; int /*<<< orphan*/  stat_reset_timestamp; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgResetsinglecounter ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ RESET_FUNCTION ; 
 scalar_t__ RESET_TABLE ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_resetsinglecounter(PgStat_MsgResetsinglecounter *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	dbentry = pgstat_get_db_entry(msg->m_databaseid, false);

	if (!dbentry)
		return;

	/* Set the reset timestamp for the whole database */
	dbentry->stat_reset_timestamp = GetCurrentTimestamp();

	/* Remove object if it exists, ignore it if not */
	if (msg->m_resettype == RESET_TABLE)
		(void) hash_search(dbentry->tables, (void *) &(msg->m_objectid),
						   HASH_REMOVE, NULL);
	else if (msg->m_resettype == RESET_FUNCTION)
		(void) hash_search(dbentry->functions, (void *) &(msg->m_objectid),
						   HASH_REMOVE, NULL);
}