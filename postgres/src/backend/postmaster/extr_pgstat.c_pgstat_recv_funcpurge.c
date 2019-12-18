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
struct TYPE_6__ {int m_nentries; int /*<<< orphan*/ * m_functionid; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  functions; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgFuncpurge ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_funcpurge(PgStat_MsgFuncpurge *msg, int len)
{
	PgStat_StatDBEntry *dbentry;
	int			i;

	dbentry = pgstat_get_db_entry(msg->m_databaseid, false);

	/*
	 * No need to purge if we don't even know the database.
	 */
	if (!dbentry || !dbentry->functions)
		return;

	/*
	 * Process all function entries in the message.
	 */
	for (i = 0; i < msg->m_nentries; i++)
	{
		/* Remove from hashtable if present; we don't care if it's not. */
		(void) hash_search(dbentry->functions,
						   (void *) &(msg->m_functionid[i]),
						   HASH_REMOVE, NULL);
	}
}