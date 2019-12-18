#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_21__ {int dtype; } ;
struct TYPE_20__ {int retisnull; scalar_t__ fn_rettype; scalar_t__ rettype; void* retval; TYPE_2__* func; scalar_t__ retistuple; TYPE_7__** datums; scalar_t__ retisset; } ;
struct TYPE_19__ {scalar_t__ rectypeid; int /*<<< orphan*/  erh; } ;
struct TYPE_18__ {size_t retvarno; int /*<<< orphan*/ * expr; } ;
struct TYPE_17__ {int isnull; TYPE_1__* datatype; void* value; } ;
struct TYPE_16__ {scalar_t__ fn_prokind; } ;
struct TYPE_15__ {scalar_t__ typoid; } ;
typedef  TYPE_3__ PLpgSQL_var ;
typedef  TYPE_4__ PLpgSQL_stmt_return ;
typedef  int /*<<< orphan*/  PLpgSQL_row ;
typedef  TYPE_5__ PLpgSQL_rec ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  TYPE_7__ PLpgSQL_datum ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 void* ExpandedRecordGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExpandedRecordIsEmpty (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
#define  PLPGSQL_DTYPE_PROMISE 131 
#define  PLPGSQL_DTYPE_REC 130 
#define  PLPGSQL_DTYPE_ROW 129 
#define  PLPGSQL_DTYPE_VAR 128 
 int PLPGSQL_RC_RETURN ; 
 scalar_t__ PROKIND_PROCEDURE ; 
 scalar_t__ VOIDOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  exec_eval_datum (TYPE_6__*,TYPE_7__*,scalar_t__*,int /*<<< orphan*/ *,void**,int*) ; 
 void* exec_eval_expr (TYPE_6__*,int /*<<< orphan*/ *,int*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_fulfill_promise (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  type_is_rowtype (scalar_t__) ; 

__attribute__((used)) static int
exec_stmt_return(PLpgSQL_execstate *estate, PLpgSQL_stmt_return *stmt)
{
	/*
	 * If processing a set-returning PL/pgSQL function, the final RETURN
	 * indicates that the function is finished producing tuples.  The rest of
	 * the work will be done at the top level.
	 */
	if (estate->retisset)
		return PLPGSQL_RC_RETURN;

	/* initialize for null result */
	estate->retval = (Datum) 0;
	estate->retisnull = true;
	estate->rettype = InvalidOid;

	/*
	 * Special case path when the RETURN expression is a simple variable
	 * reference; in particular, this path is always taken in functions with
	 * one or more OUT parameters.
	 *
	 * This special case is especially efficient for returning variables that
	 * have R/W expanded values: we can put the R/W pointer directly into
	 * estate->retval, leading to transferring the value to the caller's
	 * context cheaply.  If we went through exec_eval_expr we'd end up with a
	 * R/O pointer.  It's okay to skip MakeExpandedObjectReadOnly here since
	 * we know we won't need the variable's value within the function anymore.
	 */
	if (stmt->retvarno >= 0)
	{
		PLpgSQL_datum *retvar = estate->datums[stmt->retvarno];

		switch (retvar->dtype)
		{
			case PLPGSQL_DTYPE_PROMISE:
				/* fulfill promise if needed, then handle like regular var */
				plpgsql_fulfill_promise(estate, (PLpgSQL_var *) retvar);

				/* FALL THRU */

			case PLPGSQL_DTYPE_VAR:
				{
					PLpgSQL_var *var = (PLpgSQL_var *) retvar;

					estate->retval = var->value;
					estate->retisnull = var->isnull;
					estate->rettype = var->datatype->typoid;

					/*
					 * A PLpgSQL_var could not be of composite type, so
					 * conversion must fail if retistuple.  We throw a custom
					 * error mainly for consistency with historical behavior.
					 * For the same reason, we don't throw error if the result
					 * is NULL.  (Note that plpgsql_exec_trigger assumes that
					 * any non-null result has been verified to be composite.)
					 */
					if (estate->retistuple && !estate->retisnull)
						ereport(ERROR,
								(errcode(ERRCODE_DATATYPE_MISMATCH),
								 errmsg("cannot return non-composite value from function returning composite type")));
				}
				break;

			case PLPGSQL_DTYPE_REC:
				{
					PLpgSQL_rec *rec = (PLpgSQL_rec *) retvar;

					/* If record is empty, we return NULL not a row of nulls */
					if (rec->erh && !ExpandedRecordIsEmpty(rec->erh))
					{
						estate->retval = ExpandedRecordGetDatum(rec->erh);
						estate->retisnull = false;
						estate->rettype = rec->rectypeid;
					}
				}
				break;

			case PLPGSQL_DTYPE_ROW:
				{
					PLpgSQL_row *row = (PLpgSQL_row *) retvar;
					int32		rettypmod;

					/* We get here if there are multiple OUT parameters */
					exec_eval_datum(estate,
									(PLpgSQL_datum *) row,
									&estate->rettype,
									&rettypmod,
									&estate->retval,
									&estate->retisnull);
				}
				break;

			default:
				elog(ERROR, "unrecognized dtype: %d", retvar->dtype);
		}

		return PLPGSQL_RC_RETURN;
	}

	if (stmt->expr != NULL)
	{
		int32		rettypmod;

		estate->retval = exec_eval_expr(estate, stmt->expr,
										&(estate->retisnull),
										&(estate->rettype),
										&rettypmod);

		/*
		 * As in the DTYPE_VAR case above, throw a custom error if a non-null,
		 * non-composite value is returned in a function returning tuple.
		 */
		if (estate->retistuple && !estate->retisnull &&
			!type_is_rowtype(estate->rettype))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("cannot return non-composite value from function returning composite type")));

		return PLPGSQL_RC_RETURN;
	}

	/*
	 * Special hack for function returning VOID: instead of NULL, return a
	 * non-null VOID value.  This is of dubious importance but is kept for
	 * backwards compatibility.  We don't do it for procedures, though.
	 */
	if (estate->fn_rettype == VOIDOID &&
		estate->func->fn_prokind != PROKIND_PROCEDURE)
	{
		estate->retval = (Datum) 0;
		estate->retisnull = false;
		estate->rettype = VOIDOID;
	}

	return PLPGSQL_RC_RETURN;
}