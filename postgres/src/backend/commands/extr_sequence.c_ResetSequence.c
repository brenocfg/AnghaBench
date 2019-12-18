#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_16__ {int /*<<< orphan*/  seqstart; } ;
struct TYPE_15__ {int is_called; scalar_t__ log_cnt; int /*<<< orphan*/  last_value; } ;
struct TYPE_14__ {TYPE_1__* rd_rel; } ;
struct TYPE_13__ {int /*<<< orphan*/  last; int /*<<< orphan*/  cached; } ;
struct TYPE_12__ {scalar_t__ relfrozenxid; scalar_t__ relminmxid; int /*<<< orphan*/  relpersistence; } ;
typedef  TYPE_2__* SeqTable ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTupleData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__* Form_pg_sequence_data ;
typedef  TYPE_5__* Form_pg_sequence ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidMultiXactId ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationSetNewRelfilenode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQRELID ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_seq_with_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_sequence (int /*<<< orphan*/ ,TYPE_2__**,TYPE_3__**) ; 
 int /*<<< orphan*/  read_seq_tuple (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
ResetSequence(Oid seq_relid)
{
	Relation	seq_rel;
	SeqTable	elm;
	Form_pg_sequence_data seq;
	Buffer		buf;
	HeapTupleData seqdatatuple;
	HeapTuple	tuple;
	HeapTuple	pgstuple;
	Form_pg_sequence pgsform;
	int64		startv;

	/*
	 * Read the old sequence.  This does a bit more work than really
	 * necessary, but it's simple, and we do want to double-check that it's
	 * indeed a sequence.
	 */
	init_sequence(seq_relid, &elm, &seq_rel);
	(void) read_seq_tuple(seq_rel, &buf, &seqdatatuple);

	pgstuple = SearchSysCache1(SEQRELID, ObjectIdGetDatum(seq_relid));
	if (!HeapTupleIsValid(pgstuple))
		elog(ERROR, "cache lookup failed for sequence %u", seq_relid);
	pgsform = (Form_pg_sequence) GETSTRUCT(pgstuple);
	startv = pgsform->seqstart;
	ReleaseSysCache(pgstuple);

	/*
	 * Copy the existing sequence tuple.
	 */
	tuple = heap_copytuple(&seqdatatuple);

	/* Now we're done with the old page */
	UnlockReleaseBuffer(buf);

	/*
	 * Modify the copied tuple to execute the restart (compare the RESTART
	 * action in AlterSequence)
	 */
	seq = (Form_pg_sequence_data) GETSTRUCT(tuple);
	seq->last_value = startv;
	seq->is_called = false;
	seq->log_cnt = 0;

	/*
	 * Create a new storage file for the sequence.
	 */
	RelationSetNewRelfilenode(seq_rel, seq_rel->rd_rel->relpersistence);

	/*
	 * Ensure sequence's relfrozenxid is at 0, since it won't contain any
	 * unfrozen XIDs.  Same with relminmxid, since a sequence will never
	 * contain multixacts.
	 */
	Assert(seq_rel->rd_rel->relfrozenxid == InvalidTransactionId);
	Assert(seq_rel->rd_rel->relminmxid == InvalidMultiXactId);

	/*
	 * Insert the modified tuple into the new storage file.
	 */
	fill_seq_with_data(seq_rel, tuple);

	/* Clear local cache so that we don't think we have cached numbers */
	/* Note that we do not change the currval() state */
	elm->cached = elm->last;

	relation_close(seq_rel, NoLock);
}