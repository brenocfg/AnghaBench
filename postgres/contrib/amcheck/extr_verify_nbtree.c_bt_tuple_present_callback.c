#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  heaptuplespresent; int /*<<< orphan*/  readonly; int /*<<< orphan*/  rel; int /*<<< orphan*/  heaprel; int /*<<< orphan*/  filter; int /*<<< orphan*/  heapallindexed; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ BtreeCheckState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IndexTupleSize (TYPE_1__*) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ bloom_lacks_element (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* bt_normalize_tuple (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* index_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
bt_tuple_present_callback(Relation index, ItemPointer tid, Datum *values,
						  bool *isnull, bool tupleIsAlive, void *checkstate)
{
	BtreeCheckState *state = (BtreeCheckState *) checkstate;
	IndexTuple	itup,
				norm;

	Assert(state->heapallindexed);

	/* Generate a normalized index tuple for fingerprinting */
	itup = index_form_tuple(RelationGetDescr(index), values, isnull);
	itup->t_tid = *tid;
	norm = bt_normalize_tuple(state, itup);

	/* Probe Bloom filter -- tuple should be present */
	if (bloom_lacks_element(state->filter, (unsigned char *) norm,
							IndexTupleSize(norm)))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("heap tuple (%u,%u) from table \"%s\" lacks matching index tuple within index \"%s\"",
						ItemPointerGetBlockNumber(&(itup->t_tid)),
						ItemPointerGetOffsetNumber(&(itup->t_tid)),
						RelationGetRelationName(state->heaprel),
						RelationGetRelationName(state->rel)),
				 !state->readonly
				 ? errhint("Retrying verification using the function bt_index_parent_check() might provide a more specific error.")
				 : 0));

	state->heaptuplespresent++;
	pfree(itup);
	/* Cannot leak memory here */
	if (norm != itup)
		pfree(norm);
}