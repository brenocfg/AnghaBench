#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_15__ {int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctid; } ;
typedef  int TM_Result ;
typedef  TYPE_2__ TM_FailureData ;
typedef  TYPE_3__ SnapshotData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  int /*<<< orphan*/  IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_1__*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitDirtySnapshot (TYPE_3__) ; 
 int /*<<< orphan*/  ItemPointerIndicatesMovedPartitions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockWaitBlock ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
#define  TM_Deleted 131 
#define  TM_Invisible 130 
#define  TM_Ok 129 
#define  TM_Updated 128 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLTW_None ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_replindex_scan_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_endscan (int /*<<< orphan*/ ) ; 
 scalar_t__ index_getnext_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_rescan (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int table_tuple_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

bool
RelationFindReplTupleByIndex(Relation rel, Oid idxoid,
							 LockTupleMode lockmode,
							 TupleTableSlot *searchslot,
							 TupleTableSlot *outslot)
{
	ScanKeyData skey[INDEX_MAX_KEYS];
	IndexScanDesc scan;
	SnapshotData snap;
	TransactionId xwait;
	Relation	idxrel;
	bool		found;

	/* Open the index. */
	idxrel = index_open(idxoid, RowExclusiveLock);

	/* Start an index scan. */
	InitDirtySnapshot(snap);
	scan = index_beginscan(rel, idxrel, &snap,
						   IndexRelationGetNumberOfKeyAttributes(idxrel),
						   0);

	/* Build scan key. */
	build_replindex_scan_key(skey, rel, idxrel, searchslot);

retry:
	found = false;

	index_rescan(scan, skey, IndexRelationGetNumberOfKeyAttributes(idxrel), NULL, 0);

	/* Try to find the tuple */
	if (index_getnext_slot(scan, ForwardScanDirection, outslot))
	{
		found = true;
		ExecMaterializeSlot(outslot);

		xwait = TransactionIdIsValid(snap.xmin) ?
			snap.xmin : snap.xmax;

		/*
		 * If the tuple is locked, wait for locking transaction to finish and
		 * retry.
		 */
		if (TransactionIdIsValid(xwait))
		{
			XactLockTableWait(xwait, NULL, NULL, XLTW_None);
			goto retry;
		}
	}

	/* Found tuple, try to lock it in the lockmode. */
	if (found)
	{
		TM_FailureData tmfd;
		TM_Result	res;

		PushActiveSnapshot(GetLatestSnapshot());

		res = table_tuple_lock(rel, &(outslot->tts_tid), GetLatestSnapshot(),
							   outslot,
							   GetCurrentCommandId(false),
							   lockmode,
							   LockWaitBlock,
							   0 /* don't follow updates */ ,
							   &tmfd);

		PopActiveSnapshot();

		switch (res)
		{
			case TM_Ok:
				break;
			case TM_Updated:
				/* XXX: Improve handling here */
				if (ItemPointerIndicatesMovedPartitions(&tmfd.ctid))
					ereport(LOG,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("tuple to be locked was already moved to another partition due to concurrent update, retrying")));
				else
					ereport(LOG,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("concurrent update, retrying")));
				goto retry;
			case TM_Deleted:
				/* XXX: Improve handling here */
				ereport(LOG,
						(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
						 errmsg("concurrent delete, retrying")));
				goto retry;
			case TM_Invisible:
				elog(ERROR, "attempted to lock invisible tuple");
				break;
			default:
				elog(ERROR, "unexpected table_tuple_lock status: %u", res);
				break;
		}
	}

	index_endscan(scan);

	/* Don't release lock until commit. */
	index_close(idxrel, NoLock);

	return found;
}