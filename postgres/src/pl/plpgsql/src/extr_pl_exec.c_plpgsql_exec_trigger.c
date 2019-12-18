#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_32__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
typedef  int /*<<< orphan*/  TupleConversionMap ;
struct TYPE_41__ {int /*<<< orphan*/  tg_relation; int /*<<< orphan*/ * tg_trigtuple; int /*<<< orphan*/ * tg_newtuple; int /*<<< orphan*/  tg_event; } ;
typedef  TYPE_3__ TriggerData ;
struct TYPE_46__ {struct TYPE_46__* previous; TYPE_6__* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_45__ {scalar_t__ er_magic; } ;
struct TYPE_44__ {int /*<<< orphan*/  retval; int /*<<< orphan*/  rettype; scalar_t__ retisnull; scalar_t__ retisset; int /*<<< orphan*/ * err_text; int /*<<< orphan*/ * err_stmt; int /*<<< orphan*/  datum_context; scalar_t__* datums; TYPE_3__* trigdata; } ;
struct TYPE_43__ {size_t new_varno; size_t old_varno; scalar_t__ action; } ;
struct TYPE_42__ {int /*<<< orphan*/  erh; } ;
struct TYPE_40__ {scalar_t__ attgenerated; } ;
struct TYPE_39__ {int natts; TYPE_1__* constr; } ;
struct TYPE_38__ {scalar_t__ has_generated_stored; } ;
struct TYPE_37__ {int /*<<< orphan*/  (* func_end ) (TYPE_6__*,TYPE_5__*) ;int /*<<< orphan*/  (* func_beg ) (TYPE_6__*,TYPE_5__*) ;} ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt ;
typedef  TYPE_4__ PLpgSQL_rec ;
typedef  TYPE_5__ PLpgSQL_function ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  HeapTupleData ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_7__ ExpandedRecordHeader ;
typedef  TYPE_8__ ErrorContextCallback ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ ATTRIBUTE_GENERATED_STORED ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_S_R_E_FUNCTION_EXECUTED_NO_RETURN_STATEMENT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ER_MAGIC ; 
 int PLPGSQL_RC_RETURN ; 
 TYPE_2__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_2__*) ; 
 int /*<<< orphan*/ * SPI_copytuple (int /*<<< orphan*/ *) ; 
 int SPI_register_trigger_data (TYPE_3__*) ; 
 scalar_t__ TRIGGER_FIRED_BEFORE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_DELETE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_INSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_UPDATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_FIRED_FOR_ROW (int /*<<< orphan*/ ) ; 
 TYPE_32__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * convert_tuples_by_position (TYPE_2__*,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  copy_plpgsql_datums (TYPE_6__*,TYPE_5__*) ; 
 TYPE_2__* deconstruct_composite_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_8__* error_context_stack ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_6__*) ; 
 int /*<<< orphan*/  exec_set_found (TYPE_6__*,int) ; 
 int exec_stmt (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * execute_attr_map_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* expanded_record_get_tupdesc (TYPE_7__*) ; 
 int /*<<< orphan*/ * expanded_record_get_tuple (TYPE_7__*) ; 
 int /*<<< orphan*/  expanded_record_set_field_internal (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  expanded_record_set_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 void* gettext_noop (char*) ; 
 int /*<<< orphan*/  make_expanded_record_from_exprecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_expanded_record_from_tupdesc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plpgsql_destroy_econtext (TYPE_6__*) ; 
 int /*<<< orphan*/  plpgsql_estate_setup (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_exec_error_callback ; 
 TYPE_13__** plpgsql_plugin_ptr ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * type_is_rowtype (int /*<<< orphan*/ ) ; 

HeapTuple
plpgsql_exec_trigger(PLpgSQL_function *func,
					 TriggerData *trigdata)
{
	PLpgSQL_execstate estate;
	ErrorContextCallback plerrcontext;
	int			rc;
	TupleDesc	tupdesc;
	PLpgSQL_rec *rec_new,
			   *rec_old;
	HeapTuple	rettup;

	/*
	 * Setup the execution state
	 */
	plpgsql_estate_setup(&estate, func, NULL, NULL);
	estate.trigdata = trigdata;

	/*
	 * Setup error traceback support for ereport()
	 */
	plerrcontext.callback = plpgsql_exec_error_callback;
	plerrcontext.arg = &estate;
	plerrcontext.previous = error_context_stack;
	error_context_stack = &plerrcontext;

	/*
	 * Make local execution copies of all the datums
	 */
	estate.err_text = gettext_noop("during initialization of execution state");
	copy_plpgsql_datums(&estate, func);

	/*
	 * Put the OLD and NEW tuples into record variables
	 *
	 * We set up expanded records for both variables even though only one may
	 * have a value.  This allows record references to succeed in functions
	 * that are used for multiple trigger types.  For example, we might have a
	 * test like "if (TG_OP = 'INSERT' and NEW.foo = 'xyz')", which should
	 * work regardless of the current trigger type.  If a value is actually
	 * fetched from an unsupplied tuple, it will read as NULL.
	 */
	tupdesc = RelationGetDescr(trigdata->tg_relation);

	rec_new = (PLpgSQL_rec *) (estate.datums[func->new_varno]);
	rec_old = (PLpgSQL_rec *) (estate.datums[func->old_varno]);

	rec_new->erh = make_expanded_record_from_tupdesc(tupdesc,
													 estate.datum_context);
	rec_old->erh = make_expanded_record_from_exprecord(rec_new->erh,
													   estate.datum_context);

	if (!TRIGGER_FIRED_FOR_ROW(trigdata->tg_event))
	{
		/*
		 * Per-statement triggers don't use OLD/NEW variables
		 */
	}
	else if (TRIGGER_FIRED_BY_INSERT(trigdata->tg_event))
	{
		expanded_record_set_tuple(rec_new->erh, trigdata->tg_trigtuple,
								  false, false);
	}
	else if (TRIGGER_FIRED_BY_UPDATE(trigdata->tg_event))
	{
		expanded_record_set_tuple(rec_new->erh, trigdata->tg_newtuple,
								  false, false);
		expanded_record_set_tuple(rec_old->erh, trigdata->tg_trigtuple,
								  false, false);

		/*
		 * In BEFORE trigger, stored generated columns are not computed yet,
		 * so make them null in the NEW row.  (Only needed in UPDATE branch;
		 * in the INSERT case, they are already null, but in UPDATE, the field
		 * still contains the old value.)  Alternatively, we could construct a
		 * whole new row structure without the generated columns, but this way
		 * seems more efficient and potentially less confusing.
		 */
		if (tupdesc->constr && tupdesc->constr->has_generated_stored &&
			TRIGGER_FIRED_BEFORE(trigdata->tg_event))
		{
			for (int i = 0; i < tupdesc->natts; i++)
				if (TupleDescAttr(tupdesc, i)->attgenerated == ATTRIBUTE_GENERATED_STORED)
					expanded_record_set_field_internal(rec_new->erh,
													   i + 1,
													   (Datum) 0,
													   true,	/* isnull */
													   false, false);
		}
	}
	else if (TRIGGER_FIRED_BY_DELETE(trigdata->tg_event))
	{
		expanded_record_set_tuple(rec_old->erh, trigdata->tg_trigtuple,
								  false, false);
	}
	else
		elog(ERROR, "unrecognized trigger action: not INSERT, DELETE, or UPDATE");

	/* Make transition tables visible to this SPI connection */
	rc = SPI_register_trigger_data(trigdata);
	Assert(rc >= 0);

	estate.err_text = gettext_noop("during function entry");

	/*
	 * Set the magic variable FOUND to false
	 */
	exec_set_found(&estate, false);

	/*
	 * Let the instrumentation plugin peek at this function
	 */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->func_beg)
		((*plpgsql_plugin_ptr)->func_beg) (&estate, func);

	/*
	 * Now call the toplevel block of statements
	 */
	estate.err_text = NULL;
	estate.err_stmt = (PLpgSQL_stmt *) (func->action);
	rc = exec_stmt(&estate, (PLpgSQL_stmt *) func->action);
	if (rc != PLPGSQL_RC_RETURN)
	{
		estate.err_stmt = NULL;
		estate.err_text = NULL;
		ereport(ERROR,
				(errcode(ERRCODE_S_R_E_FUNCTION_EXECUTED_NO_RETURN_STATEMENT),
				 errmsg("control reached end of trigger procedure without RETURN")));
	}

	estate.err_stmt = NULL;
	estate.err_text = gettext_noop("during function exit");

	if (estate.retisset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("trigger procedure cannot return a set")));

	/*
	 * Check that the returned tuple structure has the same attributes, the
	 * relation that fired the trigger has. A per-statement trigger always
	 * needs to return NULL, so we ignore any return value the function itself
	 * produces (XXX: is this a good idea?)
	 *
	 * XXX This way it is possible, that the trigger returns a tuple where
	 * attributes don't have the correct atttypmod's length. It's up to the
	 * trigger's programmer to ensure that this doesn't happen. Jan
	 */
	if (estate.retisnull || !TRIGGER_FIRED_FOR_ROW(trigdata->tg_event))
		rettup = NULL;
	else
	{
		TupleDesc	retdesc;
		TupleConversionMap *tupmap;

		/* We assume exec_stmt_return verified that result is composite */
		Assert(type_is_rowtype(estate.rettype));

		/* We can special-case expanded records for speed */
		if (VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(estate.retval)))
		{
			ExpandedRecordHeader *erh = (ExpandedRecordHeader *) DatumGetEOHP(estate.retval);

			Assert(erh->er_magic == ER_MAGIC);

			/* Extract HeapTuple and TupleDesc */
			rettup = expanded_record_get_tuple(erh);
			Assert(rettup);
			retdesc = expanded_record_get_tupdesc(erh);

			if (retdesc != RelationGetDescr(trigdata->tg_relation))
			{
				/* check rowtype compatibility */
				tupmap = convert_tuples_by_position(retdesc,
													RelationGetDescr(trigdata->tg_relation),
													gettext_noop("returned row structure does not match the structure of the triggering table"));
				/* it might need conversion */
				if (tupmap)
					rettup = execute_attr_map_tuple(rettup, tupmap);
				/* no need to free map, we're about to return anyway */
			}

			/*
			 * Copy tuple to upper executor memory.  But if user just did
			 * "return new" or "return old" without changing anything, there's
			 * no need to copy; we can return the original tuple (which will
			 * save a few cycles in trigger.c as well as here).
			 */
			if (rettup != trigdata->tg_newtuple &&
				rettup != trigdata->tg_trigtuple)
				rettup = SPI_copytuple(rettup);
		}
		else
		{
			/* Convert composite datum to a HeapTuple and TupleDesc */
			HeapTupleData tmptup;

			retdesc = deconstruct_composite_datum(estate.retval, &tmptup);
			rettup = &tmptup;

			/* check rowtype compatibility */
			tupmap = convert_tuples_by_position(retdesc,
												RelationGetDescr(trigdata->tg_relation),
												gettext_noop("returned row structure does not match the structure of the triggering table"));
			/* it might need conversion */
			if (tupmap)
				rettup = execute_attr_map_tuple(rettup, tupmap);

			ReleaseTupleDesc(retdesc);
			/* no need to free map, we're about to return anyway */

			/* Copy tuple to upper executor memory */
			rettup = SPI_copytuple(rettup);
		}
	}

	/*
	 * Let the instrumentation plugin peek at this function
	 */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->func_end)
		((*plpgsql_plugin_ptr)->func_end) (&estate, func);

	/* Clean up any leftover temporary memory */
	plpgsql_destroy_econtext(&estate);
	exec_eval_cleanup(&estate);
	/* stmt_mcontext will be destroyed when function's main context is */

	/*
	 * Pop the error context stack
	 */
	error_context_stack = plerrcontext.previous;

	/*
	 * Return the trigger's result
	 */
	return rettup;
}