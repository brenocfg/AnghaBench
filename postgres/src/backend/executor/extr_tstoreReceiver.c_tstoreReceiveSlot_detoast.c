#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * tts_isnull; void** tts_values; TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_13__ {int attlen; int /*<<< orphan*/  attisdropped; } ;
struct TYPE_12__ {void** tofree; void** outvalues; int /*<<< orphan*/  tstore; int /*<<< orphan*/  cxt; } ;
struct TYPE_11__ {int natts; } ;
typedef  TYPE_3__ TStoreState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  void* Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (void*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 void* PointerGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplestore_putvalues (int /*<<< orphan*/ ,TYPE_2__*,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tstoreReceiveSlot_detoast(TupleTableSlot *slot, DestReceiver *self)
{
	TStoreState *myState = (TStoreState *) self;
	TupleDesc	typeinfo = slot->tts_tupleDescriptor;
	int			natts = typeinfo->natts;
	int			nfree;
	int			i;
	MemoryContext oldcxt;

	/* Make sure the tuple is fully deconstructed */
	slot_getallattrs(slot);

	/*
	 * Fetch back any out-of-line datums.  We build the new datums array in
	 * myState->outvalues[] (but we can re-use the slot's isnull array). Also,
	 * remember the fetched values to free afterwards.
	 */
	nfree = 0;
	for (i = 0; i < natts; i++)
	{
		Datum		val = slot->tts_values[i];
		Form_pg_attribute attr = TupleDescAttr(typeinfo, i);

		if (!attr->attisdropped && attr->attlen == -1 && !slot->tts_isnull[i])
		{
			if (VARATT_IS_EXTERNAL(DatumGetPointer(val)))
			{
				val = PointerGetDatum(detoast_external_attr((struct varlena *)
															DatumGetPointer(val)));
				myState->tofree[nfree++] = val;
			}
		}

		myState->outvalues[i] = val;
	}

	/*
	 * Push the modified tuple into the tuplestore.
	 */
	oldcxt = MemoryContextSwitchTo(myState->cxt);
	tuplestore_putvalues(myState->tstore, typeinfo,
						 myState->outvalues, slot->tts_isnull);
	MemoryContextSwitchTo(oldcxt);

	/* And release any temporary detoasted values */
	for (i = 0; i < nfree; i++)
		pfree(DatumGetPointer(myState->tofree[i]));

	return true;
}