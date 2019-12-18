#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int* tts_isnull; scalar_t__* tts_values; TYPE_10__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_18__ {struct TYPE_18__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_17__ {int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attisdropped; } ;
struct TYPE_16__ {int* attrmap; } ;
struct TYPE_15__ {int local_attnum; int remote_attnum; TYPE_3__* rel; } ;
struct TYPE_13__ {int natts; } ;
typedef  TYPE_2__ SlotErrCallbackArg ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ LogicalRepRelMapEntry ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  TYPE_5__ ErrorContextCallback ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_1__*) ; 
 scalar_t__ OidInputFunctionCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_10__*,int) ; 
 TYPE_5__* error_context_stack ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_store_error_callback ; 

__attribute__((used)) static void
slot_store_cstrings(TupleTableSlot *slot, LogicalRepRelMapEntry *rel,
					char **values)
{
	int			natts = slot->tts_tupleDescriptor->natts;
	int			i;
	SlotErrCallbackArg errarg;
	ErrorContextCallback errcallback;

	ExecClearTuple(slot);

	/* Push callback + info on the error context stack */
	errarg.rel = rel;
	errarg.local_attnum = -1;
	errarg.remote_attnum = -1;
	errcallback.callback = slot_store_error_callback;
	errcallback.arg = (void *) &errarg;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/* Call the "in" function for each non-dropped attribute */
	for (i = 0; i < natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(slot->tts_tupleDescriptor, i);
		int			remoteattnum = rel->attrmap[i];

		if (!att->attisdropped && remoteattnum >= 0 &&
			values[remoteattnum] != NULL)
		{
			Oid			typinput;
			Oid			typioparam;

			errarg.local_attnum = i;
			errarg.remote_attnum = remoteattnum;

			getTypeInputInfo(att->atttypid, &typinput, &typioparam);
			slot->tts_values[i] =
				OidInputFunctionCall(typinput, values[remoteattnum],
									 typioparam, att->atttypmod);
			slot->tts_isnull[i] = false;

			errarg.local_attnum = -1;
			errarg.remote_attnum = -1;
		}
		else
		{
			/*
			 * We assign NULL to dropped attributes, NULL values, and missing
			 * values (missing values should be later filled using
			 * slot_fill_defaults).
			 */
			slot->tts_values[i] = (Datum) 0;
			slot->tts_isnull[i] = true;
		}
	}

	/* Pop the error context stack */
	error_context_stack = errcallback.previous;

	ExecStoreVirtualTuple(slot);
}