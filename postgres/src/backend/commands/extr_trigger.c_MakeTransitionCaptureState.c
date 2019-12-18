#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int trig_insert_new_table; int trig_update_old_table; int trig_update_new_table; int trig_delete_old_table; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_9__ {int tcs_delete_old_table; int tcs_update_old_table; int tcs_update_new_table; int tcs_insert_new_table; TYPE_3__* tcs_private; } ;
typedef  TYPE_2__ TransitionCaptureState ;
struct TYPE_11__ {scalar_t__ query_depth; scalar_t__ maxquerydepth; } ;
struct TYPE_10__ {int /*<<< orphan*/ * new_tuplestore; int /*<<< orphan*/ * old_tuplestore; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int CmdType ;
typedef  TYPE_3__ AfterTriggersTableData ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerEnlargeQueryState () ; 
#define  CMD_DELETE 130 
#define  CMD_INSERT 129 
#define  CMD_UPDATE 128 
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  CurTransactionResourceOwner ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* GetAfterTriggersTableData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_4__ afterTriggers ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ palloc0 (int) ; 
 void* tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

TransitionCaptureState *
MakeTransitionCaptureState(TriggerDesc *trigdesc, Oid relid, CmdType cmdType)
{
	TransitionCaptureState *state;
	bool		need_old,
				need_new;
	AfterTriggersTableData *table;
	MemoryContext oldcxt;
	ResourceOwner saveResourceOwner;

	if (trigdesc == NULL)
		return NULL;

	/* Detect which table(s) we need. */
	switch (cmdType)
	{
		case CMD_INSERT:
			need_old = false;
			need_new = trigdesc->trig_insert_new_table;
			break;
		case CMD_UPDATE:
			need_old = trigdesc->trig_update_old_table;
			need_new = trigdesc->trig_update_new_table;
			break;
		case CMD_DELETE:
			need_old = trigdesc->trig_delete_old_table;
			need_new = false;
			break;
		default:
			elog(ERROR, "unexpected CmdType: %d", (int) cmdType);
			need_old = need_new = false;	/* keep compiler quiet */
			break;
	}
	if (!need_old && !need_new)
		return NULL;

	/* Check state, like AfterTriggerSaveEvent. */
	if (afterTriggers.query_depth < 0)
		elog(ERROR, "MakeTransitionCaptureState() called outside of query");

	/* Be sure we have enough space to record events at this query depth. */
	if (afterTriggers.query_depth >= afterTriggers.maxquerydepth)
		AfterTriggerEnlargeQueryState();

	/*
	 * Find or create an AfterTriggersTableData struct to hold the
	 * tuplestore(s).  If there's a matching struct but it's marked closed,
	 * ignore it; we need a newer one.
	 *
	 * Note: the AfterTriggersTableData list, as well as the tuplestores, are
	 * allocated in the current (sub)transaction's CurTransactionContext, and
	 * the tuplestores are managed by the (sub)transaction's resource owner.
	 * This is sufficient lifespan because we do not allow triggers using
	 * transition tables to be deferrable; they will be fired during
	 * AfterTriggerEndQuery, after which it's okay to delete the data.
	 */
	table = GetAfterTriggersTableData(relid, cmdType);

	/* Now create required tuplestore(s), if we don't have them already. */
	oldcxt = MemoryContextSwitchTo(CurTransactionContext);
	saveResourceOwner = CurrentResourceOwner;
	CurrentResourceOwner = CurTransactionResourceOwner;

	if (need_old && table->old_tuplestore == NULL)
		table->old_tuplestore = tuplestore_begin_heap(false, false, work_mem);
	if (need_new && table->new_tuplestore == NULL)
		table->new_tuplestore = tuplestore_begin_heap(false, false, work_mem);

	CurrentResourceOwner = saveResourceOwner;
	MemoryContextSwitchTo(oldcxt);

	/* Now build the TransitionCaptureState struct, in caller's context */
	state = (TransitionCaptureState *) palloc0(sizeof(TransitionCaptureState));
	state->tcs_delete_old_table = trigdesc->trig_delete_old_table;
	state->tcs_update_old_table = trigdesc->trig_update_old_table;
	state->tcs_update_new_table = trigdesc->trig_update_new_table;
	state->tcs_insert_new_table = trigdesc->trig_insert_new_table;
	state->tcs_private = table;

	return state;
}