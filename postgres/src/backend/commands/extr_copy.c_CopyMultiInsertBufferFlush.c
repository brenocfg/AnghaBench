#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_18__ {int nused; int /*<<< orphan*/ * linenos; int /*<<< orphan*/ ** slots; int /*<<< orphan*/  bistate; TYPE_2__* resultRelInfo; } ;
struct TYPE_17__ {int ti_options; int /*<<< orphan*/  mycid; TYPE_3__* estate; TYPE_4__* cstate; } ;
struct TYPE_16__ {int line_buf_valid; int /*<<< orphan*/  cur_lineno; int /*<<< orphan*/  transition_capture; } ;
struct TYPE_15__ {TYPE_2__* es_result_relation_info; } ;
struct TYPE_14__ {scalar_t__ ri_NumIndices; TYPE_1__* ri_TrigDesc; int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_13__ {scalar_t__ trig_insert_new_table; scalar_t__ trig_insert_after_row; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ EState ;
typedef  TYPE_4__* CopyState ;
typedef  TYPE_5__ CopyMultiInsertInfo ;
typedef  TYPE_6__ CopyMultiInsertBuffer ;
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  ExecARInsertTriggers (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecInsertIndexTuples (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (TYPE_3__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_multi_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
CopyMultiInsertBufferFlush(CopyMultiInsertInfo *miinfo,
						   CopyMultiInsertBuffer *buffer)
{
	MemoryContext oldcontext;
	int			i;
	uint64		save_cur_lineno;
	CopyState	cstate = miinfo->cstate;
	EState	   *estate = miinfo->estate;
	CommandId	mycid = miinfo->mycid;
	int			ti_options = miinfo->ti_options;
	bool		line_buf_valid = cstate->line_buf_valid;
	int			nused = buffer->nused;
	ResultRelInfo *resultRelInfo = buffer->resultRelInfo;
	TupleTableSlot **slots = buffer->slots;

	/* Set es_result_relation_info to the ResultRelInfo we're flushing. */
	estate->es_result_relation_info = resultRelInfo;

	/*
	 * Print error context information correctly, if one of the operations
	 * below fail.
	 */
	cstate->line_buf_valid = false;
	save_cur_lineno = cstate->cur_lineno;

	/*
	 * table_multi_insert may leak memory, so switch to short-lived memory
	 * context before calling it.
	 */
	oldcontext = MemoryContextSwitchTo(GetPerTupleMemoryContext(estate));
	table_multi_insert(resultRelInfo->ri_RelationDesc,
					   slots,
					   nused,
					   mycid,
					   ti_options,
					   buffer->bistate);
	MemoryContextSwitchTo(oldcontext);

	for (i = 0; i < nused; i++)
	{
		/*
		 * If there are any indexes, update them for all the inserted tuples,
		 * and run AFTER ROW INSERT triggers.
		 */
		if (resultRelInfo->ri_NumIndices > 0)
		{
			List	   *recheckIndexes;

			cstate->cur_lineno = buffer->linenos[i];
			recheckIndexes =
				ExecInsertIndexTuples(buffer->slots[i], estate, false, NULL,
									  NIL);
			ExecARInsertTriggers(estate, resultRelInfo,
								 slots[i], recheckIndexes,
								 cstate->transition_capture);
			list_free(recheckIndexes);
		}

		/*
		 * There's no indexes, but see if we need to run AFTER ROW INSERT
		 * triggers anyway.
		 */
		else if (resultRelInfo->ri_TrigDesc != NULL &&
				 (resultRelInfo->ri_TrigDesc->trig_insert_after_row ||
				  resultRelInfo->ri_TrigDesc->trig_insert_new_table))
		{
			cstate->cur_lineno = buffer->linenos[i];
			ExecARInsertTriggers(estate, resultRelInfo,
								 slots[i], NIL, cstate->transition_capture);
		}

		ExecClearTuple(slots[i]);
	}

	/* Mark that all slots are free */
	buffer->nused = 0;

	/* reset cur_lineno and line_buf_valid to what they were */
	cstate->line_buf_valid = line_buf_valid;
	cstate->cur_lineno = save_cur_lineno;
}