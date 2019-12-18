#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_9__ ;
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_17__ ;
typedef  struct TYPE_44__   TYPE_13__ ;
typedef  struct TYPE_43__   TYPE_12__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_49__ {int /*<<< orphan*/  tts_tid; } ;
typedef  TYPE_4__ TupleTableSlot ;
struct TYPE_50__ {int /*<<< orphan*/  attrMap; int /*<<< orphan*/  outdesc; } ;
typedef  TYPE_5__ TupleConversionMap ;
struct TYPE_51__ {int numtriggers; TYPE_7__* triggers; int /*<<< orphan*/  trig_update_after_row; int /*<<< orphan*/  trig_insert_after_row; int /*<<< orphan*/  trig_delete_after_row; } ;
typedef  TYPE_6__ TriggerDesc ;
struct TYPE_52__ {scalar_t__ tgfoid; scalar_t__ tgnewtable; scalar_t__ tgoldtable; int /*<<< orphan*/  tgoid; scalar_t__ tginitdeferred; scalar_t__ tgdeferrable; int /*<<< orphan*/  tgconstrindid; int /*<<< orphan*/  tgtype; } ;
typedef  TYPE_7__ Trigger ;
struct TYPE_53__ {int tcs_delete_old_table; int tcs_update_old_table; int tcs_update_new_table; int tcs_insert_new_table; TYPE_3__* tcs_private; TYPE_5__* tcs_map; TYPE_4__* tcs_original_insert_tuple; } ;
typedef  TYPE_8__ TransitionCaptureState ;
struct TYPE_54__ {TYPE_6__* ri_TrigDesc; TYPE_10__* ri_RelationDesc; } ;
struct TYPE_48__ {TYPE_4__* storeslot; int /*<<< orphan*/ * new_tuplestore; int /*<<< orphan*/ * old_tuplestore; } ;
struct TYPE_47__ {char relkind; } ;
struct TYPE_46__ {int /*<<< orphan*/  events; } ;
struct TYPE_45__ {size_t query_depth; size_t maxquerydepth; TYPE_1__* query_stack; } ;
struct TYPE_44__ {int /*<<< orphan*/  ate_flags; int /*<<< orphan*/  ate_ctid2; int /*<<< orphan*/  ate_ctid1; } ;
struct TYPE_43__ {int ats_event; TYPE_3__* ats_table; scalar_t__ ats_firing_id; int /*<<< orphan*/  ats_relid; int /*<<< orphan*/  ats_tgoid; } ;
struct TYPE_42__ {int /*<<< orphan*/  es_tupleTable; } ;
struct TYPE_41__ {TYPE_2__* rd_rel; } ;
typedef  TYPE_9__ ResultRelInfo ;
typedef  TYPE_10__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_11__ EState ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  TYPE_12__ AfterTriggerSharedData ;
typedef  TYPE_13__ AfterTriggerEventData ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER_TRIGGER_1CTID ; 
 int /*<<< orphan*/  AFTER_TRIGGER_2CTID ; 
 int AFTER_TRIGGER_DEFERRABLE ; 
 int /*<<< orphan*/  AFTER_TRIGGER_FDW_FETCH ; 
 int /*<<< orphan*/  AFTER_TRIGGER_FDW_REUSE ; 
 int AFTER_TRIGGER_INITDEFERRED ; 
 int /*<<< orphan*/  AfterTriggerEnlargeQueryState () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/  CMD_UPDATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_4__* ExecAllocTableSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ F_UNIQUE_KEY_RECHECK ; 
 int /*<<< orphan*/ * GetCurrentFDWTuplestore () ; 
 int /*<<< orphan*/  ItemPointerCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 char RELKIND_FOREIGN_TABLE ; 
 int /*<<< orphan*/  RI_FKey_fk_upd_check_required (TYPE_7__*,TYPE_10__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  RI_FKey_pk_upd_check_required (TYPE_7__*,TYPE_10__*,TYPE_4__*,TYPE_4__*) ; 
 int RI_FKey_trigger_type (scalar_t__) ; 
#define  RI_TRIGGER_FK 134 
#define  RI_TRIGGER_NONE 133 
#define  RI_TRIGGER_PK 132 
 int /*<<< orphan*/  RelationGetRelid (TYPE_10__*) ; 
#define  TRIGGER_EVENT_DELETE 131 
#define  TRIGGER_EVENT_INSERT 130 
 int TRIGGER_EVENT_OPMASK ; 
 int TRIGGER_EVENT_ROW ; 
#define  TRIGGER_EVENT_TRUNCATE 129 
#define  TRIGGER_EVENT_UPDATE 128 
 scalar_t__ TRIGGER_FIRED_BY_DELETE (int) ; 
 scalar_t__ TRIGGER_FIRED_BY_UPDATE (int) ; 
 int /*<<< orphan*/  TRIGGER_TYPE_AFTER ; 
 int TRIGGER_TYPE_DELETE ; 
 int TRIGGER_TYPE_INSERT ; 
 int /*<<< orphan*/  TRIGGER_TYPE_MATCHES (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int TRIGGER_TYPE_ROW ; 
 int TRIGGER_TYPE_STATEMENT ; 
 int TRIGGER_TYPE_TRUNCATE ; 
 int TRIGGER_TYPE_UPDATE ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/  TriggerEnabled (TYPE_11__*,TYPE_9__*,TYPE_7__*,int,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int TupIsNull (TYPE_4__*) ; 
 int /*<<< orphan*/  afterTriggerAddEvent (int /*<<< orphan*/ *,TYPE_13__*,TYPE_12__*) ; 
 TYPE_17__ afterTriggers ; 
 int /*<<< orphan*/  cancel_prior_stmt_triggers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  execute_attr_map_slot (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttupleslot (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
AfterTriggerSaveEvent(EState *estate, ResultRelInfo *relinfo,
					  int event, bool row_trigger,
					  TupleTableSlot *oldslot, TupleTableSlot *newslot,
					  List *recheckIndexes, Bitmapset *modifiedCols,
					  TransitionCaptureState *transition_capture)
{
	Relation	rel = relinfo->ri_RelationDesc;
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	AfterTriggerEventData new_event;
	AfterTriggerSharedData new_shared;
	char		relkind = rel->rd_rel->relkind;
	int			tgtype_event;
	int			tgtype_level;
	int			i;
	Tuplestorestate *fdw_tuplestore = NULL;

	/*
	 * Check state.  We use a normal test not Assert because it is possible to
	 * reach here in the wrong state given misconfigured RI triggers, in
	 * particular deferring a cascade action trigger.
	 */
	if (afterTriggers.query_depth < 0)
		elog(ERROR, "AfterTriggerSaveEvent() called outside of query");

	/* Be sure we have enough space to record events at this query depth. */
	if (afterTriggers.query_depth >= afterTriggers.maxquerydepth)
		AfterTriggerEnlargeQueryState();

	/*
	 * If the directly named relation has any triggers with transition tables,
	 * then we need to capture transition tuples.
	 */
	if (row_trigger && transition_capture != NULL)
	{
		TupleTableSlot *original_insert_tuple = transition_capture->tcs_original_insert_tuple;
		TupleConversionMap *map = transition_capture->tcs_map;
		bool		delete_old_table = transition_capture->tcs_delete_old_table;
		bool		update_old_table = transition_capture->tcs_update_old_table;
		bool		update_new_table = transition_capture->tcs_update_new_table;
		bool		insert_new_table = transition_capture->tcs_insert_new_table;

		/*
		 * For INSERT events NEW should be non-NULL, for DELETE events OLD
		 * should be non-NULL, whereas for UPDATE events normally both OLD and
		 * NEW are non-NULL.  But for UPDATE events fired for capturing
		 * transition tuples during UPDATE partition-key row movement, OLD is
		 * NULL when the event is for a row being inserted, whereas NEW is
		 * NULL when the event is for a row being deleted.
		 */
		Assert(!(event == TRIGGER_EVENT_DELETE && delete_old_table &&
				 TupIsNull(oldslot)));
		Assert(!(event == TRIGGER_EVENT_INSERT && insert_new_table &&
				 TupIsNull(newslot)));

		if (!TupIsNull(oldslot) &&
			((event == TRIGGER_EVENT_DELETE && delete_old_table) ||
			 (event == TRIGGER_EVENT_UPDATE && update_old_table)))
		{
			Tuplestorestate *old_tuplestore;

			old_tuplestore = transition_capture->tcs_private->old_tuplestore;

			if (map != NULL)
			{
				TupleTableSlot *storeslot;

				storeslot = transition_capture->tcs_private->storeslot;
				if (!storeslot)
				{
					storeslot = ExecAllocTableSlot(&estate->es_tupleTable,
												   map->outdesc,
												   &TTSOpsVirtual);
					transition_capture->tcs_private->storeslot = storeslot;
				}

				execute_attr_map_slot(map->attrMap, oldslot, storeslot);
				tuplestore_puttupleslot(old_tuplestore, storeslot);
			}
			else
				tuplestore_puttupleslot(old_tuplestore, oldslot);
		}
		if (!TupIsNull(newslot) &&
			((event == TRIGGER_EVENT_INSERT && insert_new_table) ||
			 (event == TRIGGER_EVENT_UPDATE && update_new_table)))
		{
			Tuplestorestate *new_tuplestore;

			new_tuplestore = transition_capture->tcs_private->new_tuplestore;

			if (original_insert_tuple != NULL)
				tuplestore_puttupleslot(new_tuplestore,
										original_insert_tuple);
			else if (map != NULL)
			{
				TupleTableSlot *storeslot;

				storeslot = transition_capture->tcs_private->storeslot;

				if (!storeslot)
				{
					storeslot = ExecAllocTableSlot(&estate->es_tupleTable,
												   map->outdesc,
												   &TTSOpsVirtual);
					transition_capture->tcs_private->storeslot = storeslot;
				}

				execute_attr_map_slot(map->attrMap, newslot, storeslot);
				tuplestore_puttupleslot(new_tuplestore, storeslot);
			}
			else
				tuplestore_puttupleslot(new_tuplestore, newslot);
		}

		/*
		 * If transition tables are the only reason we're here, return. As
		 * mentioned above, we can also be here during update tuple routing in
		 * presence of transition tables, in which case this function is
		 * called separately for oldtup and newtup, so we expect exactly one
		 * of them to be NULL.
		 */
		if (trigdesc == NULL ||
			(event == TRIGGER_EVENT_DELETE && !trigdesc->trig_delete_after_row) ||
			(event == TRIGGER_EVENT_INSERT && !trigdesc->trig_insert_after_row) ||
			(event == TRIGGER_EVENT_UPDATE && !trigdesc->trig_update_after_row) ||
			(event == TRIGGER_EVENT_UPDATE && (TupIsNull(oldslot) ^ TupIsNull(newslot))))
			return;
	}

	/*
	 * Validate the event code and collect the associated tuple CTIDs.
	 *
	 * The event code will be used both as a bitmask and an array offset, so
	 * validation is important to make sure we don't walk off the edge of our
	 * arrays.
	 *
	 * Also, if we're considering statement-level triggers, check whether we
	 * already queued a set of them for this event, and cancel the prior set
	 * if so.  This preserves the behavior that statement-level triggers fire
	 * just once per statement and fire after row-level triggers.
	 */
	switch (event)
	{
		case TRIGGER_EVENT_INSERT:
			tgtype_event = TRIGGER_TYPE_INSERT;
			if (row_trigger)
			{
				Assert(oldslot == NULL);
				Assert(newslot != NULL);
				ItemPointerCopy(&(newslot->tts_tid), &(new_event.ate_ctid1));
				ItemPointerSetInvalid(&(new_event.ate_ctid2));
			}
			else
			{
				Assert(oldslot == NULL);
				Assert(newslot == NULL);
				ItemPointerSetInvalid(&(new_event.ate_ctid1));
				ItemPointerSetInvalid(&(new_event.ate_ctid2));
				cancel_prior_stmt_triggers(RelationGetRelid(rel),
										   CMD_INSERT, event);
			}
			break;
		case TRIGGER_EVENT_DELETE:
			tgtype_event = TRIGGER_TYPE_DELETE;
			if (row_trigger)
			{
				Assert(oldslot != NULL);
				Assert(newslot == NULL);
				ItemPointerCopy(&(oldslot->tts_tid), &(new_event.ate_ctid1));
				ItemPointerSetInvalid(&(new_event.ate_ctid2));
			}
			else
			{
				Assert(oldslot == NULL);
				Assert(newslot == NULL);
				ItemPointerSetInvalid(&(new_event.ate_ctid1));
				ItemPointerSetInvalid(&(new_event.ate_ctid2));
				cancel_prior_stmt_triggers(RelationGetRelid(rel),
										   CMD_DELETE, event);
			}
			break;
		case TRIGGER_EVENT_UPDATE:
			tgtype_event = TRIGGER_TYPE_UPDATE;
			if (row_trigger)
			{
				Assert(oldslot != NULL);
				Assert(newslot != NULL);
				ItemPointerCopy(&(oldslot->tts_tid), &(new_event.ate_ctid1));
				ItemPointerCopy(&(newslot->tts_tid), &(new_event.ate_ctid2));
			}
			else
			{
				Assert(oldslot == NULL);
				Assert(newslot == NULL);
				ItemPointerSetInvalid(&(new_event.ate_ctid1));
				ItemPointerSetInvalid(&(new_event.ate_ctid2));
				cancel_prior_stmt_triggers(RelationGetRelid(rel),
										   CMD_UPDATE, event);
			}
			break;
		case TRIGGER_EVENT_TRUNCATE:
			tgtype_event = TRIGGER_TYPE_TRUNCATE;
			Assert(oldslot == NULL);
			Assert(newslot == NULL);
			ItemPointerSetInvalid(&(new_event.ate_ctid1));
			ItemPointerSetInvalid(&(new_event.ate_ctid2));
			break;
		default:
			elog(ERROR, "invalid after-trigger event code: %d", event);
			tgtype_event = 0;	/* keep compiler quiet */
			break;
	}

	if (!(relkind == RELKIND_FOREIGN_TABLE && row_trigger))
		new_event.ate_flags = (row_trigger && event == TRIGGER_EVENT_UPDATE) ?
			AFTER_TRIGGER_2CTID : AFTER_TRIGGER_1CTID;
	/* else, we'll initialize ate_flags for each trigger */

	tgtype_level = (row_trigger ? TRIGGER_TYPE_ROW : TRIGGER_TYPE_STATEMENT);

	for (i = 0; i < trigdesc->numtriggers; i++)
	{
		Trigger    *trigger = &trigdesc->triggers[i];

		if (!TRIGGER_TYPE_MATCHES(trigger->tgtype,
								  tgtype_level,
								  TRIGGER_TYPE_AFTER,
								  tgtype_event))
			continue;
		if (!TriggerEnabled(estate, relinfo, trigger, event,
							modifiedCols, oldslot, newslot))
			continue;

		if (relkind == RELKIND_FOREIGN_TABLE && row_trigger)
		{
			if (fdw_tuplestore == NULL)
			{
				fdw_tuplestore = GetCurrentFDWTuplestore();
				new_event.ate_flags = AFTER_TRIGGER_FDW_FETCH;
			}
			else
				/* subsequent event for the same tuple */
				new_event.ate_flags = AFTER_TRIGGER_FDW_REUSE;
		}

		/*
		 * If the trigger is a foreign key enforcement trigger, there are
		 * certain cases where we can skip queueing the event because we can
		 * tell by inspection that the FK constraint will still pass.
		 */
		if (TRIGGER_FIRED_BY_UPDATE(event) || TRIGGER_FIRED_BY_DELETE(event))
		{
			switch (RI_FKey_trigger_type(trigger->tgfoid))
			{
				case RI_TRIGGER_PK:
					/* Update or delete on trigger's PK table */
					if (!RI_FKey_pk_upd_check_required(trigger, rel,
													   oldslot, newslot))
					{
						/* skip queuing this event */
						continue;
					}
					break;

				case RI_TRIGGER_FK:
					/* Update on trigger's FK table */
					if (!RI_FKey_fk_upd_check_required(trigger, rel,
													   oldslot, newslot))
					{
						/* skip queuing this event */
						continue;
					}
					break;

				case RI_TRIGGER_NONE:
					/* Not an FK trigger */
					break;
			}
		}

		/*
		 * If the trigger is a deferred unique constraint check trigger, only
		 * queue it if the unique constraint was potentially violated, which
		 * we know from index insertion time.
		 */
		if (trigger->tgfoid == F_UNIQUE_KEY_RECHECK)
		{
			if (!list_member_oid(recheckIndexes, trigger->tgconstrindid))
				continue;		/* Uniqueness definitely not violated */
		}

		/*
		 * Fill in event structure and add it to the current query's queue.
		 * Note we set ats_table to NULL whenever this trigger doesn't use
		 * transition tables, to improve sharability of the shared event data.
		 */
		new_shared.ats_event =
			(event & TRIGGER_EVENT_OPMASK) |
			(row_trigger ? TRIGGER_EVENT_ROW : 0) |
			(trigger->tgdeferrable ? AFTER_TRIGGER_DEFERRABLE : 0) |
			(trigger->tginitdeferred ? AFTER_TRIGGER_INITDEFERRED : 0);
		new_shared.ats_tgoid = trigger->tgoid;
		new_shared.ats_relid = RelationGetRelid(rel);
		new_shared.ats_firing_id = 0;
		if ((trigger->tgoldtable || trigger->tgnewtable) &&
			transition_capture != NULL)
			new_shared.ats_table = transition_capture->tcs_private;
		else
			new_shared.ats_table = NULL;

		afterTriggerAddEvent(&afterTriggers.query_stack[afterTriggers.query_depth].events,
							 &new_event, &new_shared);
	}

	/*
	 * Finally, spool any foreign tuple(s).  The tuplestore squashes them to
	 * minimal tuples, so this loses any system columns.  The executor lost
	 * those columns before us, for an unrelated reason, so this is fine.
	 */
	if (fdw_tuplestore)
	{
		if (oldslot != NULL)
			tuplestore_puttupleslot(fdw_tuplestore, oldslot);
		if (newslot != NULL)
			tuplestore_puttupleslot(fdw_tuplestore, newslot);
	}
}