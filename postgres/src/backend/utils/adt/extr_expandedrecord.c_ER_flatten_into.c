#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_17__ {scalar_t__ er_magic; int flags; scalar_t__ flat_size; int hoff; scalar_t__ hasnull; int /*<<< orphan*/  data_len; int /*<<< orphan*/  dnulls; int /*<<< orphan*/  dvalues; int /*<<< orphan*/  er_typmod; int /*<<< orphan*/  er_typeid; TYPE_1__* fvalue; } ;
struct TYPE_16__ {int t_hoff; int /*<<< orphan*/ * t_bits; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_15__ {int /*<<< orphan*/  natts; } ;
struct TYPE_14__ {scalar_t__ t_len; int /*<<< orphan*/  t_data; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_3__* HeapTupleHeader ;
typedef  TYPE_4__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int ER_FLAG_FVALUE_VALID ; 
 int ER_FLAG_HAVE_EXTERNAL ; 
 scalar_t__ ER_MAGIC ; 
 int /*<<< orphan*/  HeapTupleHeaderSetDatumLength (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetNatts (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetTypMod (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetTypeId (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 TYPE_2__* expanded_record_get_tupdesc (TYPE_4__*) ; 
 int /*<<< orphan*/  heap_fill_tuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ER_flatten_into(ExpandedObjectHeader *eohptr,
				void *result, Size allocated_size)
{
	ExpandedRecordHeader *erh = (ExpandedRecordHeader *) eohptr;
	HeapTupleHeader tuphdr = (HeapTupleHeader) result;
	TupleDesc	tupdesc;

	Assert(erh->er_magic == ER_MAGIC);

	/* Easy if we have a valid flattened value without out-of-line fields */
	if (erh->flags & ER_FLAG_FVALUE_VALID &&
		!(erh->flags & ER_FLAG_HAVE_EXTERNAL))
	{
		Assert(allocated_size == erh->fvalue->t_len);
		memcpy(tuphdr, erh->fvalue->t_data, allocated_size);
		/* The original flattened value might not have datum header fields */
		HeapTupleHeaderSetDatumLength(tuphdr, allocated_size);
		HeapTupleHeaderSetTypeId(tuphdr, erh->er_typeid);
		HeapTupleHeaderSetTypMod(tuphdr, erh->er_typmod);
		return;
	}

	/* Else allocation should match previous get_flat_size result */
	Assert(allocated_size == erh->flat_size);

	/* We'll need the tuple descriptor */
	tupdesc = expanded_record_get_tupdesc(erh);

	/* We must ensure that any pad space is zero-filled */
	memset(tuphdr, 0, allocated_size);

	/* Set up header fields of composite Datum */
	HeapTupleHeaderSetDatumLength(tuphdr, allocated_size);
	HeapTupleHeaderSetTypeId(tuphdr, erh->er_typeid);
	HeapTupleHeaderSetTypMod(tuphdr, erh->er_typmod);
	/* We also make sure that t_ctid is invalid unless explicitly set */
	ItemPointerSetInvalid(&(tuphdr->t_ctid));

	HeapTupleHeaderSetNatts(tuphdr, tupdesc->natts);
	tuphdr->t_hoff = erh->hoff;

	/* And fill the data area from dvalues/dnulls */
	heap_fill_tuple(tupdesc,
					erh->dvalues,
					erh->dnulls,
					(char *) tuphdr + erh->hoff,
					erh->data_len,
					&tuphdr->t_infomask,
					(erh->hasnull ? tuphdr->t_bits : NULL));
}