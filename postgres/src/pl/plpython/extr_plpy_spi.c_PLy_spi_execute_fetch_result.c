#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_13__ {int /*<<< orphan*/  curr_proc; } ;
struct TYPE_12__ {struct TYPE_12__* rows; int /*<<< orphan*/  tupdesc; struct TYPE_12__* nrows; struct TYPE_12__* status; } ;
struct TYPE_11__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ SPITupleTable ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PLyResultObject ;
typedef  TYPE_3__ PLyExecutionContext ;
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  volatile MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  volatile AllocSetContextCreate (int /*<<< orphan*/  volatile,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  volatile CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  volatile MemoryContextSwitchTo (int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_3__* PLy_current_execution_context () ; 
 int /*<<< orphan*/ * PLy_input_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLy_input_setup_func (int /*<<< orphan*/ *,int /*<<< orphan*/  volatile,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLy_input_setup_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PLy_result_new () ; 
 scalar_t__ PY_SSIZE_T_MAX ; 
 TYPE_2__* PyInt_FromLong (int) ; 
 TYPE_2__* PyList_New (scalar_t__) ; 
 int /*<<< orphan*/  PyList_SetItem (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 void* PyLong_FromUnsignedLongLong (scalar_t__) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  RECORDOID ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_1__*) ; 
 int /*<<< orphan*/  volatile TopMemoryContext ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static PyObject *
PLy_spi_execute_fetch_result(SPITupleTable *tuptable, uint64 rows, int status)
{
	PLyResultObject *result;
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();
	volatile MemoryContext oldcontext;

	result = (PLyResultObject *) PLy_result_new();
	if (!result)
	{
		SPI_freetuptable(tuptable);
		return NULL;
	}
	Py_DECREF(result->status);
	result->status = PyInt_FromLong(status);

	if (status > 0 && tuptable == NULL)
	{
		Py_DECREF(result->nrows);
		result->nrows = PyLong_FromUnsignedLongLong(rows);
	}
	else if (status > 0 && tuptable != NULL)
	{
		PLyDatumToOb ininfo;
		MemoryContext cxt;

		Py_DECREF(result->nrows);
		result->nrows = PyLong_FromUnsignedLongLong(rows);

		cxt = AllocSetContextCreate(CurrentMemoryContext,
									"PL/Python temp context",
									ALLOCSET_DEFAULT_SIZES);

		/* Initialize for converting result tuples to Python */
		PLy_input_setup_func(&ininfo, cxt, RECORDOID, -1,
							 exec_ctx->curr_proc);

		oldcontext = CurrentMemoryContext;
		PG_TRY();
		{
			MemoryContext oldcontext2;

			if (rows)
			{
				uint64		i;

				/*
				 * PyList_New() and PyList_SetItem() use Py_ssize_t for list
				 * size and list indices; so we cannot support a result larger
				 * than PY_SSIZE_T_MAX.
				 */
				if (rows > (uint64) PY_SSIZE_T_MAX)
					ereport(ERROR,
							(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
							 errmsg("query result has too many rows to fit in a Python list")));

				Py_DECREF(result->rows);
				result->rows = PyList_New(rows);
				if (result->rows)
				{
					PLy_input_setup_tuple(&ininfo, tuptable->tupdesc,
										  exec_ctx->curr_proc);

					for (i = 0; i < rows; i++)
					{
						PyObject   *row = PLy_input_from_tuple(&ininfo,
															   tuptable->vals[i],
															   tuptable->tupdesc,
															   true);

						PyList_SetItem(result->rows, i, row);
					}
				}
			}

			/*
			 * Save tuple descriptor for later use by result set metadata
			 * functions.  Save it in TopMemoryContext so that it survives
			 * outside of an SPI context.  We trust that PLy_result_dealloc()
			 * will clean it up when the time is right.  (Do this as late as
			 * possible, to minimize the number of ways the tupdesc could get
			 * leaked due to errors.)
			 */
			oldcontext2 = MemoryContextSwitchTo(TopMemoryContext);
			result->tupdesc = CreateTupleDescCopy(tuptable->tupdesc);
			MemoryContextSwitchTo(oldcontext2);
		}
		PG_CATCH();
		{
			MemoryContextSwitchTo(oldcontext);
			MemoryContextDelete(cxt);
			Py_DECREF(result);
			PG_RE_THROW();
		}
		PG_END_TRY();

		MemoryContextDelete(cxt);
		SPI_freetuptable(tuptable);

		/* in case PyList_New() failed above */
		if (!result->rows)
		{
			Py_DECREF(result);
			result = NULL;
		}
	}

	return (PyObject *) result;
}