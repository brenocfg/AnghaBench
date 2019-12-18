#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_18__ {int /*<<< orphan*/ * additional; } ;
typedef  TYPE_3__ TupleHashEntryData ;
struct TYPE_20__ {size_t current_set; int numtrans; int /*<<< orphan*/ * pertrans; TYPE_4__* perhash; TYPE_1__* tmpcontext; } ;
struct TYPE_19__ {int numhashGrpCols; int* hashGrpColIdxInput; TYPE_11__* hashtable; int /*<<< orphan*/  largestGrpColIdx; TYPE_2__* hashslot; } ;
struct TYPE_16__ {TYPE_2__* ecxt_outertuple; } ;
struct TYPE_15__ {int /*<<< orphan*/  tablecxt; } ;
typedef  int /*<<< orphan*/ * AggStatePerTrans ;
typedef  TYPE_4__* AggStatePerHash ;
typedef  int /*<<< orphan*/  AggStatePerGroupData ;
typedef  int /*<<< orphan*/ * AggStatePerGroup ;
typedef  TYPE_5__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_2__*) ; 
 TYPE_3__* LookupTupleHashEntry (TYPE_11__*,TYPE_2__*,int*) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initialize_aggregate (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_getsomeattrs (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleHashEntryData *
lookup_hash_entry(AggState *aggstate)
{
	TupleTableSlot *inputslot = aggstate->tmpcontext->ecxt_outertuple;
	AggStatePerHash perhash = &aggstate->perhash[aggstate->current_set];
	TupleTableSlot *hashslot = perhash->hashslot;
	TupleHashEntryData *entry;
	bool		isnew;
	int			i;

	/* transfer just the needed columns into hashslot */
	slot_getsomeattrs(inputslot, perhash->largestGrpColIdx);
	ExecClearTuple(hashslot);

	for (i = 0; i < perhash->numhashGrpCols; i++)
	{
		int			varNumber = perhash->hashGrpColIdxInput[i] - 1;

		hashslot->tts_values[i] = inputslot->tts_values[varNumber];
		hashslot->tts_isnull[i] = inputslot->tts_isnull[varNumber];
	}
	ExecStoreVirtualTuple(hashslot);

	/* find or create the hashtable entry using the filtered tuple */
	entry = LookupTupleHashEntry(perhash->hashtable, hashslot, &isnew);

	if (isnew)
	{
		AggStatePerGroup pergroup;
		int			transno;

		pergroup = (AggStatePerGroup)
			MemoryContextAlloc(perhash->hashtable->tablecxt,
							   sizeof(AggStatePerGroupData) * aggstate->numtrans);
		entry->additional = pergroup;

		/*
		 * Initialize aggregates for new tuple group, lookup_hash_entries()
		 * already has selected the relevant grouping set.
		 */
		for (transno = 0; transno < aggstate->numtrans; transno++)
		{
			AggStatePerTrans pertrans = &aggstate->pertrans[transno];
			AggStatePerGroup pergroupstate = &pergroup[transno];

			initialize_aggregate(aggstate, pertrans, pergroupstate);
		}
	}

	return entry;
}