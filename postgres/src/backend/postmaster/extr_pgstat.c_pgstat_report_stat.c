#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_8__ {scalar_t__ tsa_used; TYPE_2__* tsa_entries; struct TYPE_8__* tsa_next; } ;
typedef  TYPE_1__ TabStatusArray ;
struct TYPE_11__ {size_t m_nentries; TYPE_3__* m_entry; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_counts; int /*<<< orphan*/  t_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_counts; int /*<<< orphan*/  t_id; scalar_t__ t_shared; int /*<<< orphan*/ * trans; } ;
typedef  TYPE_2__ PgStat_TableStatus ;
typedef  TYPE_3__ PgStat_TableEntry ;
typedef  int /*<<< orphan*/  PgStat_TableCounts ;
typedef  TYPE_4__ PgStat_MsgTabstat ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTransactionStopTimestamp () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 size_t PGSTAT_NUM_TABENTRIES ; 
 int /*<<< orphan*/  PGSTAT_STAT_INTERVAL ; 
 int /*<<< orphan*/  TimestampDifferenceExceeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_function_stats ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pgStatTabHash ; 
 TYPE_1__* pgStatTabList ; 
 scalar_t__ pgStatXactCommit ; 
 scalar_t__ pgStatXactRollback ; 
 int /*<<< orphan*/  pgstat_send_funcstats () ; 
 int /*<<< orphan*/  pgstat_send_tabstat (TYPE_4__*) ; 

void
pgstat_report_stat(bool force)
{
	/* we assume this inits to all zeroes: */
	static const PgStat_TableCounts all_zeroes;
	static TimestampTz last_report = 0;

	TimestampTz now;
	PgStat_MsgTabstat regular_msg;
	PgStat_MsgTabstat shared_msg;
	TabStatusArray *tsa;
	int			i;

	/* Don't expend a clock check if nothing to do */
	if ((pgStatTabList == NULL || pgStatTabList->tsa_used == 0) &&
		pgStatXactCommit == 0 && pgStatXactRollback == 0 &&
		!have_function_stats)
		return;

	/*
	 * Don't send a message unless it's been at least PGSTAT_STAT_INTERVAL
	 * msec since we last sent one, or the caller wants to force stats out.
	 */
	now = GetCurrentTransactionStopTimestamp();
	if (!force &&
		!TimestampDifferenceExceeds(last_report, now, PGSTAT_STAT_INTERVAL))
		return;
	last_report = now;

	/*
	 * Destroy pgStatTabHash before we start invalidating PgStat_TableEntry
	 * entries it points to.  (Should we fail partway through the loop below,
	 * it's okay to have removed the hashtable already --- the only
	 * consequence is we'd get multiple entries for the same table in the
	 * pgStatTabList, and that's safe.)
	 */
	if (pgStatTabHash)
		hash_destroy(pgStatTabHash);
	pgStatTabHash = NULL;

	/*
	 * Scan through the TabStatusArray struct(s) to find tables that actually
	 * have counts, and build messages to send.  We have to separate shared
	 * relations from regular ones because the databaseid field in the message
	 * header has to depend on that.
	 */
	regular_msg.m_databaseid = MyDatabaseId;
	shared_msg.m_databaseid = InvalidOid;
	regular_msg.m_nentries = 0;
	shared_msg.m_nentries = 0;

	for (tsa = pgStatTabList; tsa != NULL; tsa = tsa->tsa_next)
	{
		for (i = 0; i < tsa->tsa_used; i++)
		{
			PgStat_TableStatus *entry = &tsa->tsa_entries[i];
			PgStat_MsgTabstat *this_msg;
			PgStat_TableEntry *this_ent;

			/* Shouldn't have any pending transaction-dependent counts */
			Assert(entry->trans == NULL);

			/*
			 * Ignore entries that didn't accumulate any actual counts, such
			 * as indexes that were opened by the planner but not used.
			 */
			if (memcmp(&entry->t_counts, &all_zeroes,
					   sizeof(PgStat_TableCounts)) == 0)
				continue;

			/*
			 * OK, insert data into the appropriate message, and send if full.
			 */
			this_msg = entry->t_shared ? &shared_msg : &regular_msg;
			this_ent = &this_msg->m_entry[this_msg->m_nentries];
			this_ent->t_id = entry->t_id;
			memcpy(&this_ent->t_counts, &entry->t_counts,
				   sizeof(PgStat_TableCounts));
			if (++this_msg->m_nentries >= PGSTAT_NUM_TABENTRIES)
			{
				pgstat_send_tabstat(this_msg);
				this_msg->m_nentries = 0;
			}
		}
		/* zero out PgStat_TableStatus structs after use */
		MemSet(tsa->tsa_entries, 0,
			   tsa->tsa_used * sizeof(PgStat_TableStatus));
		tsa->tsa_used = 0;
	}

	/*
	 * Send partial messages.  Make sure that any pending xact commit/abort
	 * gets counted, even if there are no table stats to send.
	 */
	if (regular_msg.m_nentries > 0 ||
		pgStatXactCommit > 0 || pgStatXactRollback > 0)
		pgstat_send_tabstat(&regular_msg);
	if (shared_msg.m_nentries > 0)
		pgstat_send_tabstat(&shared_msg);

	/* Now, send function statistics */
	pgstat_send_funcstats();
}