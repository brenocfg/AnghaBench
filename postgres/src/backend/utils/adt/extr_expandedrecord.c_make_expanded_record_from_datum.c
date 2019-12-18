#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* fstartptr; char* fendptr; int /*<<< orphan*/  hdr; int /*<<< orphan*/  flags; TYPE_2__* fvalue; int /*<<< orphan*/  er_typmod; int /*<<< orphan*/  er_typeid; int /*<<< orphan*/  er_decltypeid; int /*<<< orphan*/  er_magic; } ;
struct TYPE_7__ {int t_len; scalar_t__ t_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_1__ HeapTupleData ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOHPGetRWDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EOH_init_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ER_FLAG_FVALUE_ALLOCED ; 
 int /*<<< orphan*/  ER_FLAG_FVALUE_VALID ; 
 int /*<<< orphan*/  ER_MAGIC ; 
 int /*<<< orphan*/  ER_methods ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderHasExternal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_copytuple (TYPE_1__*) ; 

Datum
make_expanded_record_from_datum(Datum recorddatum, MemoryContext parentcontext)
{
	ExpandedRecordHeader *erh;
	HeapTupleHeader tuphdr;
	HeapTupleData tmptup;
	HeapTuple	newtuple;
	MemoryContext objcxt;
	MemoryContext oldcxt;

	/*
	 * Allocate private context for expanded object.  We use a regular-size
	 * context, not a small one, to improve the odds that we can fit a tupdesc
	 * into it without needing an extra malloc block.
	 */
	objcxt = AllocSetContextCreate(parentcontext,
								   "expanded record",
								   ALLOCSET_DEFAULT_SIZES);

	/* Set up expanded record header, initializing fields to 0/null */
	erh = (ExpandedRecordHeader *)
		MemoryContextAllocZero(objcxt, sizeof(ExpandedRecordHeader));

	EOH_init_header(&erh->hdr, &ER_methods, objcxt);
	erh->er_magic = ER_MAGIC;

	/*
	 * Detoast and copy source record into private context, as a HeapTuple.
	 * (If we actually have to detoast the source, we'll leak some memory in
	 * the caller's context, but it doesn't seem worth worrying about.)
	 */
	tuphdr = DatumGetHeapTupleHeader(recorddatum);

	tmptup.t_len = HeapTupleHeaderGetDatumLength(tuphdr);
	ItemPointerSetInvalid(&(tmptup.t_self));
	tmptup.t_tableOid = InvalidOid;
	tmptup.t_data = tuphdr;

	oldcxt = MemoryContextSwitchTo(objcxt);
	newtuple = heap_copytuple(&tmptup);
	erh->flags |= ER_FLAG_FVALUE_ALLOCED;
	MemoryContextSwitchTo(oldcxt);

	/* Fill in composite-type identification info */
	erh->er_decltypeid = erh->er_typeid = HeapTupleHeaderGetTypeId(tuphdr);
	erh->er_typmod = HeapTupleHeaderGetTypMod(tuphdr);

	/* remember we have a flat representation */
	erh->fvalue = newtuple;
	erh->fstartptr = (char *) newtuple->t_data;
	erh->fendptr = ((char *) newtuple->t_data) + newtuple->t_len;
	erh->flags |= ER_FLAG_FVALUE_VALID;

	/* Shouldn't need to set ER_FLAG_HAVE_EXTERNAL */
	Assert(!HeapTupleHeaderHasExternal(tuphdr));

	/*
	 * We won't look up the tupdesc till we have to, nor make a deconstructed
	 * representation.  We don't have enough info to fill flat_size and
	 * friends, either.
	 */

	/* return a R/W pointer to the expanded record */
	return EOHPGetRWDatum(&erh->hdr);
}