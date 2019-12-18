#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__* evtrigdata; TYPE_2__* trigdata; int /*<<< orphan*/  datum_context; } ;
struct TYPE_18__ {int promise; } ;
struct TYPE_17__ {char* event; char* tag; } ;
struct TYPE_16__ {TYPE_1__* tg_trigger; TYPE_12__* tg_relation; int /*<<< orphan*/  tg_event; } ;
struct TYPE_15__ {int tgnargs; int /*<<< orphan*/ * tgargs; int /*<<< orphan*/  tgname; } ;
struct TYPE_14__ {int /*<<< orphan*/  rd_id; } ;
typedef  TYPE_4__ PLpgSQL_var ;
typedef  TYPE_5__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetTextDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PLPGSQL_PROMISE_NONE ; 
#define  PLPGSQL_PROMISE_TG_ARGV 138 
#define  PLPGSQL_PROMISE_TG_EVENT 137 
#define  PLPGSQL_PROMISE_TG_LEVEL 136 
#define  PLPGSQL_PROMISE_TG_NAME 135 
#define  PLPGSQL_PROMISE_TG_NARGS 134 
#define  PLPGSQL_PROMISE_TG_OP 133 
#define  PLPGSQL_PROMISE_TG_RELID 132 
#define  PLPGSQL_PROMISE_TG_TABLE_NAME 131 
#define  PLPGSQL_PROMISE_TG_TABLE_SCHEMA 130 
#define  PLPGSQL_PROMISE_TG_TAG 129 
#define  PLPGSQL_PROMISE_TG_WHEN 128 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetNamespace (TYPE_12__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_12__*) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TRIGGER_FIRED_AFTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_BEFORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_BY_DELETE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_BY_INSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_BY_TRUNCATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_BY_UPDATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_FOR_ROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_FOR_STATEMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_INSTEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_simple_var (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assign_text_var (TYPE_5__*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  construct_md_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ ,int,int,char) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/ * palloc (int) ; 

__attribute__((used)) static void
plpgsql_fulfill_promise(PLpgSQL_execstate *estate,
						PLpgSQL_var *var)
{
	MemoryContext oldcontext;

	if (var->promise == PLPGSQL_PROMISE_NONE)
		return;					/* nothing to do */

	/*
	 * This will typically be invoked in a short-lived context such as the
	 * mcontext.  We must create variable values in the estate's datum
	 * context.  This quick-and-dirty solution risks leaking some additional
	 * cruft there, but since any one promise is honored at most once per
	 * function call, it's probably not worth being more careful.
	 */
	oldcontext = MemoryContextSwitchTo(estate->datum_context);

	switch (var->promise)
	{
		case PLPGSQL_PROMISE_TG_NAME:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			assign_simple_var(estate, var,
							  DirectFunctionCall1(namein,
												  CStringGetDatum(estate->trigdata->tg_trigger->tgname)),
							  false, true);
			break;

		case PLPGSQL_PROMISE_TG_WHEN:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			if (TRIGGER_FIRED_BEFORE(estate->trigdata->tg_event))
				assign_text_var(estate, var, "BEFORE");
			else if (TRIGGER_FIRED_AFTER(estate->trigdata->tg_event))
				assign_text_var(estate, var, "AFTER");
			else if (TRIGGER_FIRED_INSTEAD(estate->trigdata->tg_event))
				assign_text_var(estate, var, "INSTEAD OF");
			else
				elog(ERROR, "unrecognized trigger execution time: not BEFORE, AFTER, or INSTEAD OF");
			break;

		case PLPGSQL_PROMISE_TG_LEVEL:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			if (TRIGGER_FIRED_FOR_ROW(estate->trigdata->tg_event))
				assign_text_var(estate, var, "ROW");
			else if (TRIGGER_FIRED_FOR_STATEMENT(estate->trigdata->tg_event))
				assign_text_var(estate, var, "STATEMENT");
			else
				elog(ERROR, "unrecognized trigger event type: not ROW or STATEMENT");
			break;

		case PLPGSQL_PROMISE_TG_OP:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			if (TRIGGER_FIRED_BY_INSERT(estate->trigdata->tg_event))
				assign_text_var(estate, var, "INSERT");
			else if (TRIGGER_FIRED_BY_UPDATE(estate->trigdata->tg_event))
				assign_text_var(estate, var, "UPDATE");
			else if (TRIGGER_FIRED_BY_DELETE(estate->trigdata->tg_event))
				assign_text_var(estate, var, "DELETE");
			else if (TRIGGER_FIRED_BY_TRUNCATE(estate->trigdata->tg_event))
				assign_text_var(estate, var, "TRUNCATE");
			else
				elog(ERROR, "unrecognized trigger action: not INSERT, DELETE, UPDATE, or TRUNCATE");
			break;

		case PLPGSQL_PROMISE_TG_RELID:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			assign_simple_var(estate, var,
							  ObjectIdGetDatum(estate->trigdata->tg_relation->rd_id),
							  false, false);
			break;

		case PLPGSQL_PROMISE_TG_TABLE_NAME:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			assign_simple_var(estate, var,
							  DirectFunctionCall1(namein,
												  CStringGetDatum(RelationGetRelationName(estate->trigdata->tg_relation))),
							  false, true);
			break;

		case PLPGSQL_PROMISE_TG_TABLE_SCHEMA:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			assign_simple_var(estate, var,
							  DirectFunctionCall1(namein,
												  CStringGetDatum(get_namespace_name(RelationGetNamespace(estate->trigdata->tg_relation)))),
							  false, true);
			break;

		case PLPGSQL_PROMISE_TG_NARGS:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			assign_simple_var(estate, var,
							  Int16GetDatum(estate->trigdata->tg_trigger->tgnargs),
							  false, false);
			break;

		case PLPGSQL_PROMISE_TG_ARGV:
			if (estate->trigdata == NULL)
				elog(ERROR, "trigger promise is not in a trigger function");
			if (estate->trigdata->tg_trigger->tgnargs > 0)
			{
				/*
				 * For historical reasons, tg_argv[] subscripts start at zero
				 * not one.  So we can't use construct_array().
				 */
				int			nelems = estate->trigdata->tg_trigger->tgnargs;
				Datum	   *elems;
				int			dims[1];
				int			lbs[1];
				int			i;

				elems = palloc(sizeof(Datum) * nelems);
				for (i = 0; i < nelems; i++)
					elems[i] = CStringGetTextDatum(estate->trigdata->tg_trigger->tgargs[i]);
				dims[0] = nelems;
				lbs[0] = 0;

				assign_simple_var(estate, var,
								  PointerGetDatum(construct_md_array(elems, NULL,
																	 1, dims, lbs,
																	 TEXTOID,
																	 -1, false, 'i')),
								  false, true);
			}
			else
			{
				assign_simple_var(estate, var, (Datum) 0, true, false);
			}
			break;

		case PLPGSQL_PROMISE_TG_EVENT:
			if (estate->evtrigdata == NULL)
				elog(ERROR, "event trigger promise is not in an event trigger function");
			assign_text_var(estate, var, estate->evtrigdata->event);
			break;

		case PLPGSQL_PROMISE_TG_TAG:
			if (estate->evtrigdata == NULL)
				elog(ERROR, "event trigger promise is not in an event trigger function");
			assign_text_var(estate, var, estate->evtrigdata->tag);
			break;

		default:
			elog(ERROR, "unrecognized promise type: %d", var->promise);
	}

	MemoryContextSwitchTo(oldcontext);
}