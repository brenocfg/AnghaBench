#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogSegNo ;
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  void* TransactionId ;
struct TYPE_8__ {scalar_t__ confirmed_flush; scalar_t__ restart_lsn; void* catalog_xmin; void* xmin; } ;
struct TYPE_11__ {TYPE_2__ data; int /*<<< orphan*/  mutex; void* effective_catalog_xmin; void* effective_xmin; } ;
struct TYPE_10__ {TYPE_3__* replication_slots; } ;
struct TYPE_7__ {scalar_t__ restart_lsn; scalar_t__ persistency; int /*<<< orphan*/  name; void* catalog_xmin; void* xmin; int /*<<< orphan*/  plugin; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; TYPE_1__ data; void* effective_catalog_xmin; void* effective_xmin; scalar_t__ in_use; } ;
typedef  TYPE_3__ ReplicationSlot ;
typedef  int /*<<< orphan*/ * Name ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckLogicalDecodingRequirements () ; 
 int /*<<< orphan*/  CheckSlotRequirements () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSNGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_6__* MyReplicationSlot ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_NAME (int) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  PG_RETURN_DATUM (int /*<<< orphan*/ ) ; 
 scalar_t__ RS_TEMPORARY ; 
 int /*<<< orphan*/  ReplicationSlotControlLock ; 
 TYPE_5__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  ReplicationSlotMarkDirty () ; 
 int /*<<< orphan*/  ReplicationSlotPersist () ; 
 int /*<<< orphan*/  ReplicationSlotRelease () ; 
 int /*<<< orphan*/  ReplicationSlotSave () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredLSN () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredXmin (int) ; 
 int SlotIsLogical (TYPE_3__*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  XLByteToSeg (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogGetLastRemovedSegno () ; 
 scalar_t__ XLogRecPtrIsInvalid (scalar_t__) ; 
 int /*<<< orphan*/  check_permissions () ; 
 int /*<<< orphan*/  create_logical_replication_slot (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  create_physical_replication_slot (char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int max_replication_slots ; 
 char* pstrdup (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static Datum
copy_replication_slot(FunctionCallInfo fcinfo, bool logical_slot)
{
	Name		src_name = PG_GETARG_NAME(0);
	Name		dst_name = PG_GETARG_NAME(1);
	ReplicationSlot *src = NULL;
	XLogRecPtr	src_restart_lsn;
	bool		src_islogical;
	bool		temporary;
	char	   *plugin;
	Datum		values[2];
	bool		nulls[2];
	Datum		result;
	TupleDesc	tupdesc;
	HeapTuple	tuple;

	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "return type must be a row type");

	check_permissions();

	if (logical_slot)
		CheckLogicalDecodingRequirements();
	else
		CheckSlotRequirements();

	LWLockAcquire(ReplicationSlotControlLock, LW_SHARED);

	/*
	 * We need to prevent the source slot's reserved WAL from being removed,
	 * but we don't want to lock that slot for very long, and it can advance
	 * in the meantime.  So obtain the source slot's data, and create a new
	 * slot using its restart_lsn.  Afterwards we lock the source slot again
	 * and verify that the data we copied (name, type) has not changed
	 * incompatibly.  No inconvenient WAL removal can occur once the new slot
	 * is created -- but since WAL removal could have occurred before we
	 * managed to create the new slot, we advance the new slot's restart_lsn
	 * to the source slot's updated restart_lsn the second time we lock it.
	 */
	for (int i = 0; i < max_replication_slots; i++)
	{
		ReplicationSlot *s = &ReplicationSlotCtl->replication_slots[i];

		if (s->in_use && strcmp(NameStr(s->data.name), NameStr(*src_name)) == 0)
		{
			SpinLockAcquire(&s->mutex);
			src_islogical = SlotIsLogical(s);
			src_restart_lsn = s->data.restart_lsn;
			temporary = s->data.persistency == RS_TEMPORARY;
			plugin = logical_slot ? pstrdup(NameStr(s->data.plugin)) : NULL;
			SpinLockRelease(&s->mutex);

			src = s;
			break;
		}
	}

	LWLockRelease(ReplicationSlotControlLock);

	if (src == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("replication slot \"%s\" does not exist", NameStr(*src_name))));

	/* Check type of replication slot */
	if (src_islogical != logical_slot)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 src_islogical ?
				 errmsg("cannot copy physical replication slot \"%s\" as a logical replication slot",
						NameStr(*src_name)) :
				 errmsg("cannot copy logical replication slot \"%s\" as a physical replication slot",
						NameStr(*src_name))));

	/* Copying non-reserved slot doesn't make sense */
	if (XLogRecPtrIsInvalid(src_restart_lsn))
	{
		Assert(!logical_slot);
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 (errmsg("cannot copy a replication slot that doesn't reserve WAL"))));
	}

	/* Overwrite params from optional arguments */
	if (PG_NARGS() >= 3)
		temporary = PG_GETARG_BOOL(2);
	if (PG_NARGS() >= 4)
	{
		Assert(logical_slot);
		plugin = NameStr(*(PG_GETARG_NAME(3)));
	}

	/* Create new slot and acquire it */
	if (logical_slot)
		create_logical_replication_slot(NameStr(*dst_name),
										plugin,
										temporary,
										src_restart_lsn);
	else
		create_physical_replication_slot(NameStr(*dst_name),
										 true,
										 temporary,
										 src_restart_lsn);

	/*
	 * Update the destination slot to current values of the source slot;
	 * recheck that the source slot is still the one we saw previously.
	 */
	{
		TransactionId copy_effective_xmin;
		TransactionId copy_effective_catalog_xmin;
		TransactionId copy_xmin;
		TransactionId copy_catalog_xmin;
		XLogRecPtr	copy_restart_lsn;
		bool		copy_islogical;
		char	   *copy_name;

		/* Copy data of source slot again */
		SpinLockAcquire(&src->mutex);
		copy_effective_xmin = src->effective_xmin;
		copy_effective_catalog_xmin = src->effective_catalog_xmin;

		copy_xmin = src->data.xmin;
		copy_catalog_xmin = src->data.catalog_xmin;
		copy_restart_lsn = src->data.restart_lsn;

		/* for existence check */
		copy_name = pstrdup(NameStr(src->data.name));
		copy_islogical = SlotIsLogical(src);
		SpinLockRelease(&src->mutex);

		/*
		 * Check if the source slot still exists and is valid. We regard it as
		 * invalid if the type of replication slot or name has been changed,
		 * or the restart_lsn either is invalid or has gone backward. (The
		 * restart_lsn could go backwards if the source slot is dropped and
		 * copied from an older slot during installation.)
		 *
		 * Since erroring out will release and drop the destination slot we
		 * don't need to release it here.
		 */
		if (copy_restart_lsn < src_restart_lsn ||
			src_islogical != copy_islogical ||
			strcmp(copy_name, NameStr(*src_name)) != 0)
			ereport(ERROR,
					(errmsg("could not copy replication slot \"%s\"",
							NameStr(*src_name)),
					 errdetail("The source replication slot was modified incompatibly during the copy operation.")));

		/* Install copied values again */
		SpinLockAcquire(&MyReplicationSlot->mutex);
		MyReplicationSlot->effective_xmin = copy_effective_xmin;
		MyReplicationSlot->effective_catalog_xmin = copy_effective_catalog_xmin;

		MyReplicationSlot->data.xmin = copy_xmin;
		MyReplicationSlot->data.catalog_xmin = copy_catalog_xmin;
		MyReplicationSlot->data.restart_lsn = copy_restart_lsn;
		SpinLockRelease(&MyReplicationSlot->mutex);

		ReplicationSlotMarkDirty();
		ReplicationSlotsComputeRequiredXmin(false);
		ReplicationSlotsComputeRequiredLSN();
		ReplicationSlotSave();

#ifdef USE_ASSERT_CHECKING
		/* Check that the restart_lsn is available */
		{
			XLogSegNo	segno;

			XLByteToSeg(copy_restart_lsn, segno, wal_segment_size);
			Assert(XLogGetLastRemovedSegno() < segno);
		}
#endif
	}

	/* target slot fully created, mark as persistent if needed */
	if (logical_slot && !temporary)
		ReplicationSlotPersist();

	/* All done.  Set up the return values */
	values[0] = NameGetDatum(dst_name);
	nulls[0] = false;
	if (!XLogRecPtrIsInvalid(MyReplicationSlot->data.confirmed_flush))
	{
		values[1] = LSNGetDatum(MyReplicationSlot->data.confirmed_flush);
		nulls[1] = false;
	}
	else
		nulls[1] = true;

	tuple = heap_form_tuple(tupdesc, values, nulls);
	result = HeapTupleGetDatum(tuple);

	ReplicationSlotRelease();

	PG_RETURN_DATUM(result);
}