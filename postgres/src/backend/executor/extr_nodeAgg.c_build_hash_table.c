#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* state; } ;
struct TYPE_16__ {TYPE_10__ ps; } ;
struct TYPE_19__ {scalar_t__ aggstrategy; int numtrans; int num_hashes; int /*<<< orphan*/  aggsplit; TYPE_6__* hashcontext; TYPE_5__ ss; TYPE_7__* perhash; TYPE_1__* tmpcontext; } ;
struct TYPE_18__ {TYPE_3__* aggnode; int /*<<< orphan*/  hashfunctions; int /*<<< orphan*/  eqfuncoids; int /*<<< orphan*/  hashGrpColIdxHash; int /*<<< orphan*/  numCols; TYPE_2__* hashslot; scalar_t__ hashtable; } ;
struct TYPE_17__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_15__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_14__ {scalar_t__ numGroups; int /*<<< orphan*/  grpCollations; } ;
struct TYPE_13__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
struct TYPE_12__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_7__* AggStatePerHash ;
typedef  int /*<<< orphan*/  AggStatePerGroupData ;
typedef  TYPE_8__ AggState ;

/* Variables and functions */
 scalar_t__ AGG_HASHED ; 
 scalar_t__ AGG_MIXED ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BuildTupleHashTableExt (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_AGGSPLIT_SKIPFINAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetTupleHashTable (scalar_t__) ; 

__attribute__((used)) static void
build_hash_table(AggState *aggstate)
{
	MemoryContext tmpmem = aggstate->tmpcontext->ecxt_per_tuple_memory;
	Size		additionalsize;
	int			i;

	Assert(aggstate->aggstrategy == AGG_HASHED || aggstate->aggstrategy == AGG_MIXED);

	additionalsize = aggstate->numtrans * sizeof(AggStatePerGroupData);

	for (i = 0; i < aggstate->num_hashes; ++i)
	{
		AggStatePerHash perhash = &aggstate->perhash[i];

		Assert(perhash->aggnode->numGroups > 0);

		if (perhash->hashtable)
			ResetTupleHashTable(perhash->hashtable);
		else
			perhash->hashtable = BuildTupleHashTableExt(&aggstate->ss.ps,
														perhash->hashslot->tts_tupleDescriptor,
														perhash->numCols,
														perhash->hashGrpColIdxHash,
														perhash->eqfuncoids,
														perhash->hashfunctions,
														perhash->aggnode->grpCollations,
														perhash->aggnode->numGroups,
														additionalsize,
														aggstate->ss.ps.state->es_query_cxt,
														aggstate->hashcontext->ecxt_per_tuple_memory,
														tmpmem,
														DO_AGGSPLIT_SKIPFINAL(aggstate->aggsplit));
	}
}