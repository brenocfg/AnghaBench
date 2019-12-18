#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_15__ {int m_resetcounter; void* m_dead_tuples; void* m_live_tuples; int /*<<< orphan*/  m_analyzetime; int /*<<< orphan*/  m_autovacuum; int /*<<< orphan*/  m_tableoid; int /*<<< orphan*/  m_databaseid; int /*<<< orphan*/  m_hdr; } ;
struct TYPE_14__ {scalar_t__ tuples_deleted; scalar_t__ tuples_updated; scalar_t__ tuples_inserted; struct TYPE_14__* upper; } ;
struct TYPE_13__ {TYPE_3__* rd_rel; TYPE_2__* pgstat_info; } ;
struct TYPE_12__ {scalar_t__ relisshared; } ;
struct TYPE_10__ {scalar_t__ t_delta_dead_tuples; } ;
struct TYPE_11__ {TYPE_1__ t_counts; TYPE_5__* trans; } ;
typedef  TYPE_4__* Relation ;
typedef  TYPE_5__ PgStat_TableXactStatus ;
typedef  TYPE_6__ PgStat_MsgAnalyze ;
typedef  void* PgStat_Counter ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsAutoVacuumWorkerProcess () ; 
 void* Max (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PGSTAT_MTYPE_ANALYZE ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 scalar_t__ pgStatSock ; 
 int /*<<< orphan*/  pgstat_send (TYPE_6__*,int) ; 
 int /*<<< orphan*/  pgstat_setheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_track_counts ; 

void
pgstat_report_analyze(Relation rel,
					  PgStat_Counter livetuples, PgStat_Counter deadtuples,
					  bool resetcounter)
{
	PgStat_MsgAnalyze msg;

	if (pgStatSock == PGINVALID_SOCKET || !pgstat_track_counts)
		return;

	/*
	 * Unlike VACUUM, ANALYZE might be running inside a transaction that has
	 * already inserted and/or deleted rows in the target table. ANALYZE will
	 * have counted such rows as live or dead respectively. Because we will
	 * report our counts of such rows at transaction end, we should subtract
	 * off these counts from what we send to the collector now, else they'll
	 * be double-counted after commit.  (This approach also ensures that the
	 * collector ends up with the right numbers if we abort instead of
	 * committing.)
	 */
	if (rel->pgstat_info != NULL)
	{
		PgStat_TableXactStatus *trans;

		for (trans = rel->pgstat_info->trans; trans; trans = trans->upper)
		{
			livetuples -= trans->tuples_inserted - trans->tuples_deleted;
			deadtuples -= trans->tuples_updated + trans->tuples_deleted;
		}
		/* count stuff inserted by already-aborted subxacts, too */
		deadtuples -= rel->pgstat_info->t_counts.t_delta_dead_tuples;
		/* Since ANALYZE's counts are estimates, we could have underflowed */
		livetuples = Max(livetuples, 0);
		deadtuples = Max(deadtuples, 0);
	}

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_ANALYZE);
	msg.m_databaseid = rel->rd_rel->relisshared ? InvalidOid : MyDatabaseId;
	msg.m_tableoid = RelationGetRelid(rel);
	msg.m_autovacuum = IsAutoVacuumWorkerProcess();
	msg.m_resetcounter = resetcounter;
	msg.m_analyzetime = GetCurrentTimestamp();
	msg.m_live_tuples = livetuples;
	msg.m_dead_tuples = deadtuples;
	pgstat_send(&msg, sizeof(msg));
}