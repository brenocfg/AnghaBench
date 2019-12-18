#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int natts; } ;
struct TYPE_13__ {TYPE_2__* bt_columns; } ;
struct TYPE_12__ {int bs_currRangeStart; int bs_pagesPerRange; TYPE_2__* bs_bdesc; TYPE_5__* bs_dtuple; } ;
struct TYPE_11__ {TYPE_8__* bd_tupdesc; } ;
struct TYPE_10__ {int /*<<< orphan*/  attcollation; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ BrinValues ;
typedef  TYPE_3__ BrinBuildState ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_PROCNUM_ADDVALUE ; 
 int /*<<< orphan*/  BRIN_elog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FunctionCall4Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 TYPE_1__* TupleDescAttr (TYPE_8__*,int) ; 
 int /*<<< orphan*/  brin_memtuple_initialize (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  form_and_insert_tuple (TYPE_3__*) ; 
 int /*<<< orphan*/ * index_getprocinfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brinbuildCallback(Relation index,
				  ItemPointer tid,
				  Datum *values,
				  bool *isnull,
				  bool tupleIsAlive,
				  void *brstate)
{
	BrinBuildState *state = (BrinBuildState *) brstate;
	BlockNumber thisblock;
	int			i;

	thisblock = ItemPointerGetBlockNumber(tid);

	/*
	 * If we're in a block that belongs to a future range, summarize what
	 * we've got and start afresh.  Note the scan might have skipped many
	 * pages, if they were devoid of live tuples; make sure to insert index
	 * tuples for those too.
	 */
	while (thisblock > state->bs_currRangeStart + state->bs_pagesPerRange - 1)
	{

		BRIN_elog((DEBUG2,
				   "brinbuildCallback: completed a range: %u--%u",
				   state->bs_currRangeStart,
				   state->bs_currRangeStart + state->bs_pagesPerRange));

		/* create the index tuple and insert it */
		form_and_insert_tuple(state);

		/* set state to correspond to the next range */
		state->bs_currRangeStart += state->bs_pagesPerRange;

		/* re-initialize state for it */
		brin_memtuple_initialize(state->bs_dtuple, state->bs_bdesc);
	}

	/* Accumulate the current tuple into the running state */
	for (i = 0; i < state->bs_bdesc->bd_tupdesc->natts; i++)
	{
		FmgrInfo   *addValue;
		BrinValues *col;
		Form_pg_attribute attr = TupleDescAttr(state->bs_bdesc->bd_tupdesc, i);

		col = &state->bs_dtuple->bt_columns[i];
		addValue = index_getprocinfo(index, i + 1,
									 BRIN_PROCNUM_ADDVALUE);

		/*
		 * Update dtuple state, if and as necessary.
		 */
		FunctionCall4Coll(addValue,
						  attr->attcollation,
						  PointerGetDatum(state->bs_bdesc),
						  PointerGetDatum(col),
						  values[i], isnull[i]);
	}
}