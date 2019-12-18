#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_15__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_14__ {int /*<<< orphan*/  result; int /*<<< orphan*/  portalname; scalar_t__ closed; } ;
struct TYPE_13__ {int /*<<< orphan*/  curr_proc; } ;
struct TYPE_12__ {struct TYPE_12__* rows; struct TYPE_12__* nrows; struct TYPE_12__* status; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Portal ;
typedef  TYPE_1__ PLyResultObject ;
typedef  TYPE_2__ PLyExecutionContext ;
typedef  TYPE_3__ PLyCursorObject ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_2__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PLy_input_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLy_input_setup_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PLy_result_new () ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_abort (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_begin (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_commit (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 scalar_t__ PY_SSIZE_T_MAX ; 
 int /*<<< orphan*/  PortalIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 TYPE_1__* PyInt_FromLong (int /*<<< orphan*/ ) ; 
 TYPE_1__* PyList_New (scalar_t__) ; 
 int /*<<< orphan*/  PyList_SetItem (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* PyLong_FromUnsignedLongLong (scalar_t__) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  SPI_OK_FETCH ; 
 int /*<<< orphan*/  SPI_cursor_fetch (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_4__*) ; 
 scalar_t__ SPI_processed ; 
 TYPE_4__* SPI_tuptable ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static PyObject *
PLy_cursor_fetch(PyObject *self, PyObject *args)
{
	PLyCursorObject *cursor;
	int			count;
	PLyResultObject *ret;
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();
	volatile MemoryContext oldcontext;
	volatile ResourceOwner oldowner;
	Portal		portal;

	if (!PyArg_ParseTuple(args, "i:fetch", &count))
		return NULL;

	cursor = (PLyCursorObject *) self;

	if (cursor->closed)
	{
		PLy_exception_set(PyExc_ValueError, "fetch from a closed cursor");
		return NULL;
	}

	portal = GetPortalByName(cursor->portalname);
	if (!PortalIsValid(portal))
	{
		PLy_exception_set(PyExc_ValueError,
						  "iterating a cursor in an aborted subtransaction");
		return NULL;
	}

	ret = (PLyResultObject *) PLy_result_new();
	if (ret == NULL)
		return NULL;

	oldcontext = CurrentMemoryContext;
	oldowner = CurrentResourceOwner;

	PLy_spi_subtransaction_begin(oldcontext, oldowner);

	PG_TRY();
	{
		SPI_cursor_fetch(portal, true, count);

		Py_DECREF(ret->status);
		ret->status = PyInt_FromLong(SPI_OK_FETCH);

		Py_DECREF(ret->nrows);
		ret->nrows = PyLong_FromUnsignedLongLong(SPI_processed);

		if (SPI_processed != 0)
		{
			uint64		i;

			/*
			 * PyList_New() and PyList_SetItem() use Py_ssize_t for list size
			 * and list indices; so we cannot support a result larger than
			 * PY_SSIZE_T_MAX.
			 */
			if (SPI_processed > (uint64) PY_SSIZE_T_MAX)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("query result has too many rows to fit in a Python list")));

			Py_DECREF(ret->rows);
			ret->rows = PyList_New(SPI_processed);
			if (!ret->rows)
			{
				Py_DECREF(ret);
				ret = NULL;
			}
			else
			{
				PLy_input_setup_tuple(&cursor->result, SPI_tuptable->tupdesc,
									  exec_ctx->curr_proc);

				for (i = 0; i < SPI_processed; i++)
				{
					PyObject   *row = PLy_input_from_tuple(&cursor->result,
														   SPI_tuptable->vals[i],
														   SPI_tuptable->tupdesc,
														   true);

					PyList_SetItem(ret->rows, i, row);
				}
			}
		}

		SPI_freetuptable(SPI_tuptable);

		PLy_spi_subtransaction_commit(oldcontext, oldowner);
	}
	PG_CATCH();
	{
		PLy_spi_subtransaction_abort(oldcontext, oldowner);
		return NULL;
	}
	PG_END_TRY();

	return (PyObject *) ret;
}