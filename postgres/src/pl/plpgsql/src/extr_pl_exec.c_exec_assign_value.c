#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;

/* Type definitions */
typedef  void* int32 ;
typedef  void* int16 ;
struct TYPE_33__ {int /*<<< orphan*/  er_tupdesc_id; } ;
struct TYPE_32__ {size_t arrayparentno; void* parenttypoid; void* parenttypmod; int elemtypbyval; char elemtypalign; void* arraytypmod; void* arraytypoid; void* elemtyplen; void* arraytyplen; void* elemtypoid; int /*<<< orphan*/ * subscript; } ;
struct TYPE_31__ {int dtype; } ;
struct TYPE_30__ {int /*<<< orphan*/ * eval_tuptable; TYPE_6__** datums; int /*<<< orphan*/  atomic; int /*<<< orphan*/  datum_context; } ;
struct TYPE_29__ {int /*<<< orphan*/  refname; TYPE_8__* erh; int /*<<< orphan*/  notnull; } ;
struct TYPE_25__ {int /*<<< orphan*/  fnumber; void* ftypmod; void* ftypeid; } ;
struct TYPE_28__ {size_t recparentno; TYPE_14__ finfo; int /*<<< orphan*/  fieldname; int /*<<< orphan*/  rectupledescid; } ;
struct TYPE_27__ {int /*<<< orphan*/  promise; TYPE_1__* datatype; int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; int /*<<< orphan*/  refname; int /*<<< orphan*/  notnull; } ;
struct TYPE_26__ {int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  typisarray; void* atttypmod; void* typoid; } ;
typedef  int /*<<< orphan*/  SPITupleTable ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  int /*<<< orphan*/  PLpgSQL_row ;
typedef  TYPE_3__ PLpgSQL_recfield ;
typedef  TYPE_4__ PLpgSQL_rec ;
typedef  int /*<<< orphan*/  PLpgSQL_expr ;
typedef  TYPE_5__ PLpgSQL_execstate ;
typedef  TYPE_6__ PLpgSQL_datum ;
typedef  TYPE_7__ PLpgSQL_arrayelem ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_8__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXDIM ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
#define  PLPGSQL_DTYPE_ARRAYELEM 133 
#define  PLPGSQL_DTYPE_PROMISE 132 
#define  PLPGSQL_DTYPE_REC 131 
#define  PLPGSQL_DTYPE_RECFIELD 130 
#define  PLPGSQL_DTYPE_ROW 129 
#define  PLPGSQL_DTYPE_VAR 128 
 int /*<<< orphan*/  PLPGSQL_PROMISE_NONE ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_freetuptable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_set_element (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int,void*,void*,int,char) ; 
 int /*<<< orphan*/  assign_simple_var (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  construct_empty_array (void*) ; 
 int /*<<< orphan*/  datumTransfer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exec_cast_value (TYPE_5__*,int /*<<< orphan*/ ,int*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  exec_eval_datum (TYPE_5__*,TYPE_6__*,void**,void**,int /*<<< orphan*/ *,int*) ; 
 int exec_eval_integer (TYPE_5__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  exec_move_row (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_move_row_from_datum (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expanded_record_lookup_field (TYPE_8__*,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  expanded_record_set_field (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* getBaseTypeAndTypmod (void*,void**) ; 
 void* get_element_type (void*) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_5__*) ; 
 void* get_typlen (void*) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (void*,void**,int*,char*) ; 
 int /*<<< orphan*/  instantiate_empty_record_variable (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  type_is_rowtype (void*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static void
exec_assign_value(PLpgSQL_execstate *estate,
				  PLpgSQL_datum *target,
				  Datum value, bool isNull,
				  Oid valtype, int32 valtypmod)
{
	switch (target->dtype)
	{
		case PLPGSQL_DTYPE_VAR:
		case PLPGSQL_DTYPE_PROMISE:
			{
				/*
				 * Target is a variable
				 */
				PLpgSQL_var *var = (PLpgSQL_var *) target;
				Datum		newvalue;

				newvalue = exec_cast_value(estate,
										   value,
										   &isNull,
										   valtype,
										   valtypmod,
										   var->datatype->typoid,
										   var->datatype->atttypmod);

				if (isNull && var->notnull)
					ereport(ERROR,
							(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
							 errmsg("null value cannot be assigned to variable \"%s\" declared NOT NULL",
									var->refname)));

				/*
				 * If type is by-reference, copy the new value (which is
				 * probably in the eval_mcontext) into the procedure's main
				 * memory context.  But if it's a read/write reference to an
				 * expanded object, no physical copy needs to happen; at most
				 * we need to reparent the object's memory context.
				 *
				 * If it's an array, we force the value to be stored in R/W
				 * expanded form.  This wins if the function later does, say,
				 * a lot of array subscripting operations on the variable, and
				 * otherwise might lose.  We might need to use a different
				 * heuristic, but it's too soon to tell.  Also, are there
				 * cases where it'd be useful to force non-array values into
				 * expanded form?
				 */
				if (!var->datatype->typbyval && !isNull)
				{
					if (var->datatype->typisarray &&
						!VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(newvalue)))
					{
						/* array and not already R/W, so apply expand_array */
						newvalue = expand_array(newvalue,
												estate->datum_context,
												NULL);
					}
					else
					{
						/* else transfer value if R/W, else just datumCopy */
						newvalue = datumTransfer(newvalue,
												 false,
												 var->datatype->typlen);
					}
				}

				/*
				 * Now free the old value, if any, and assign the new one. But
				 * skip the assignment if old and new values are the same.
				 * Note that for expanded objects, this test is necessary and
				 * cannot reliably be made any earlier; we have to be looking
				 * at the object's standard R/W pointer to be sure pointer
				 * equality is meaningful.
				 *
				 * Also, if it's a promise variable, we should disarm the
				 * promise in any case --- otherwise, assigning null to an
				 * armed promise variable would fail to disarm the promise.
				 */
				if (var->value != newvalue || var->isnull || isNull)
					assign_simple_var(estate, var, newvalue, isNull,
									  (!var->datatype->typbyval && !isNull));
				else
					var->promise = PLPGSQL_PROMISE_NONE;
				break;
			}

		case PLPGSQL_DTYPE_ROW:
			{
				/*
				 * Target is a row variable
				 */
				PLpgSQL_row *row = (PLpgSQL_row *) target;

				if (isNull)
				{
					/* If source is null, just assign nulls to the row */
					exec_move_row(estate, (PLpgSQL_variable *) row,
								  NULL, NULL);
				}
				else
				{
					/* Source must be of RECORD or composite type */
					if (!type_is_rowtype(valtype))
						ereport(ERROR,
								(errcode(ERRCODE_DATATYPE_MISMATCH),
								 errmsg("cannot assign non-composite value to a row variable")));
					exec_move_row_from_datum(estate, (PLpgSQL_variable *) row,
											 value);
				}
				break;
			}

		case PLPGSQL_DTYPE_REC:
			{
				/*
				 * Target is a record variable
				 */
				PLpgSQL_rec *rec = (PLpgSQL_rec *) target;

				if (isNull)
				{
					if (rec->notnull)
						ereport(ERROR,
								(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
								 errmsg("null value cannot be assigned to variable \"%s\" declared NOT NULL",
										rec->refname)));

					/* Set variable to a simple NULL */
					exec_move_row(estate, (PLpgSQL_variable *) rec,
								  NULL, NULL);
				}
				else
				{
					/* Source must be of RECORD or composite type */
					if (!type_is_rowtype(valtype))
						ereport(ERROR,
								(errcode(ERRCODE_DATATYPE_MISMATCH),
								 errmsg("cannot assign non-composite value to a record variable")));
					exec_move_row_from_datum(estate, (PLpgSQL_variable *) rec,
											 value);
				}
				break;
			}

		case PLPGSQL_DTYPE_RECFIELD:
			{
				/*
				 * Target is a field of a record
				 */
				PLpgSQL_recfield *recfield = (PLpgSQL_recfield *) target;
				PLpgSQL_rec *rec;
				ExpandedRecordHeader *erh;

				rec = (PLpgSQL_rec *) (estate->datums[recfield->recparentno]);
				erh = rec->erh;

				/*
				 * If record variable is NULL, instantiate it if it has a
				 * named composite type, else complain.  (This won't change
				 * the logical state of the record, but if we successfully
				 * assign below, the unassigned fields will all become NULLs.)
				 */
				if (erh == NULL)
				{
					instantiate_empty_record_variable(estate, rec);
					erh = rec->erh;
				}

				/*
				 * Look up the field's properties if we have not already, or
				 * if the tuple descriptor ID changed since last time.
				 */
				if (unlikely(recfield->rectupledescid != erh->er_tupdesc_id))
				{
					if (!expanded_record_lookup_field(erh,
													  recfield->fieldname,
													  &recfield->finfo))
						ereport(ERROR,
								(errcode(ERRCODE_UNDEFINED_COLUMN),
								 errmsg("record \"%s\" has no field \"%s\"",
										rec->refname, recfield->fieldname)));
					recfield->rectupledescid = erh->er_tupdesc_id;
				}

				/* We don't support assignments to system columns. */
				if (recfield->finfo.fnumber <= 0)
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("cannot assign to system column \"%s\"",
									recfield->fieldname)));

				/* Cast the new value to the right type, if needed. */
				value = exec_cast_value(estate,
										value,
										&isNull,
										valtype,
										valtypmod,
										recfield->finfo.ftypeid,
										recfield->finfo.ftypmod);

				/* And assign it. */
				expanded_record_set_field(erh, recfield->finfo.fnumber,
										  value, isNull, !estate->atomic);
				break;
			}

		case PLPGSQL_DTYPE_ARRAYELEM:
			{
				/*
				 * Target is an element of an array
				 */
				PLpgSQL_arrayelem *arrayelem;
				int			nsubscripts;
				int			i;
				PLpgSQL_expr *subscripts[MAXDIM];
				int			subscriptvals[MAXDIM];
				Datum		oldarraydatum,
							newarraydatum,
							coerced_value;
				bool		oldarrayisnull;
				Oid			parenttypoid;
				int32		parenttypmod;
				SPITupleTable *save_eval_tuptable;
				MemoryContext oldcontext;

				/*
				 * We need to do subscript evaluation, which might require
				 * evaluating general expressions; and the caller might have
				 * done that too in order to prepare the input Datum.  We have
				 * to save and restore the caller's SPI_execute result, if
				 * any.
				 */
				save_eval_tuptable = estate->eval_tuptable;
				estate->eval_tuptable = NULL;

				/*
				 * To handle constructs like x[1][2] := something, we have to
				 * be prepared to deal with a chain of arrayelem datums. Chase
				 * back to find the base array datum, and save the subscript
				 * expressions as we go.  (We are scanning right to left here,
				 * but want to evaluate the subscripts left-to-right to
				 * minimize surprises.)  Note that arrayelem is left pointing
				 * to the leftmost arrayelem datum, where we will cache the
				 * array element type data.
				 */
				nsubscripts = 0;
				do
				{
					arrayelem = (PLpgSQL_arrayelem *) target;
					if (nsubscripts >= MAXDIM)
						ereport(ERROR,
								(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
								 errmsg("number of array dimensions (%d) exceeds the maximum allowed (%d)",
										nsubscripts + 1, MAXDIM)));
					subscripts[nsubscripts++] = arrayelem->subscript;
					target = estate->datums[arrayelem->arrayparentno];
				} while (target->dtype == PLPGSQL_DTYPE_ARRAYELEM);

				/* Fetch current value of array datum */
				exec_eval_datum(estate, target,
								&parenttypoid, &parenttypmod,
								&oldarraydatum, &oldarrayisnull);

				/* Update cached type data if necessary */
				if (arrayelem->parenttypoid != parenttypoid ||
					arrayelem->parenttypmod != parenttypmod)
				{
					Oid			arraytypoid;
					int32		arraytypmod = parenttypmod;
					int16		arraytyplen;
					Oid			elemtypoid;
					int16		elemtyplen;
					bool		elemtypbyval;
					char		elemtypalign;

					/* If target is domain over array, reduce to base type */
					arraytypoid = getBaseTypeAndTypmod(parenttypoid,
													   &arraytypmod);

					/* ... and identify the element type */
					elemtypoid = get_element_type(arraytypoid);
					if (!OidIsValid(elemtypoid))
						ereport(ERROR,
								(errcode(ERRCODE_DATATYPE_MISMATCH),
								 errmsg("subscripted object is not an array")));

					/* Collect needed data about the types */
					arraytyplen = get_typlen(arraytypoid);

					get_typlenbyvalalign(elemtypoid,
										 &elemtyplen,
										 &elemtypbyval,
										 &elemtypalign);

					/* Now safe to update the cached data */
					arrayelem->parenttypoid = parenttypoid;
					arrayelem->parenttypmod = parenttypmod;
					arrayelem->arraytypoid = arraytypoid;
					arrayelem->arraytypmod = arraytypmod;
					arrayelem->arraytyplen = arraytyplen;
					arrayelem->elemtypoid = elemtypoid;
					arrayelem->elemtyplen = elemtyplen;
					arrayelem->elemtypbyval = elemtypbyval;
					arrayelem->elemtypalign = elemtypalign;
				}

				/*
				 * Evaluate the subscripts, switch into left-to-right order.
				 * Like the expression built by ExecInitSubscriptingRef(),
				 * complain if any subscript is null.
				 */
				for (i = 0; i < nsubscripts; i++)
				{
					bool		subisnull;

					subscriptvals[i] =
						exec_eval_integer(estate,
										  subscripts[nsubscripts - 1 - i],
										  &subisnull);
					if (subisnull)
						ereport(ERROR,
								(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
								 errmsg("array subscript in assignment must not be null")));

					/*
					 * Clean up in case the subscript expression wasn't
					 * simple. We can't do exec_eval_cleanup, but we can do
					 * this much (which is safe because the integer subscript
					 * value is surely pass-by-value), and we must do it in
					 * case the next subscript expression isn't simple either.
					 */
					if (estate->eval_tuptable != NULL)
						SPI_freetuptable(estate->eval_tuptable);
					estate->eval_tuptable = NULL;
				}

				/* Now we can restore caller's SPI_execute result if any. */
				Assert(estate->eval_tuptable == NULL);
				estate->eval_tuptable = save_eval_tuptable;

				/* Coerce source value to match array element type. */
				coerced_value = exec_cast_value(estate,
												value,
												&isNull,
												valtype,
												valtypmod,
												arrayelem->elemtypoid,
												arrayelem->arraytypmod);

				/*
				 * If the original array is null, cons up an empty array so
				 * that the assignment can proceed; we'll end with a
				 * one-element array containing just the assigned-to
				 * subscript.  This only works for varlena arrays, though; for
				 * fixed-length array types we skip the assignment.  We can't
				 * support assignment of a null entry into a fixed-length
				 * array, either, so that's a no-op too.  This is all ugly but
				 * corresponds to the current behavior of execExpr*.c.
				 */
				if (arrayelem->arraytyplen > 0 &&	/* fixed-length array? */
					(oldarrayisnull || isNull))
					return;

				/* empty array, if any, and newarraydatum are short-lived */
				oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));

				if (oldarrayisnull)
					oldarraydatum = PointerGetDatum(construct_empty_array(arrayelem->elemtypoid));

				/*
				 * Build the modified array value.
				 */
				newarraydatum = array_set_element(oldarraydatum,
												  nsubscripts,
												  subscriptvals,
												  coerced_value,
												  isNull,
												  arrayelem->arraytyplen,
												  arrayelem->elemtyplen,
												  arrayelem->elemtypbyval,
												  arrayelem->elemtypalign);

				MemoryContextSwitchTo(oldcontext);

				/*
				 * Assign the new array to the base variable.  It's never NULL
				 * at this point.  Note that if the target is a domain,
				 * coercing the base array type back up to the domain will
				 * happen within exec_assign_value.
				 */
				exec_assign_value(estate, target,
								  newarraydatum,
								  false,
								  arrayelem->arraytypoid,
								  arrayelem->arraytypmod);
				break;
			}

		default:
			elog(ERROR, "unrecognized dtype: %d", target->dtype);
	}
}