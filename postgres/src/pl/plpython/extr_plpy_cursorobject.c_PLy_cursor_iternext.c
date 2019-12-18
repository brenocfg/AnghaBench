#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_7__ {int /*<<< orphan*/  result; int /*<<< orphan*/  portalname; scalar_t__ closed; } ;
struct TYPE_6__ {int /*<<< orphan*/  curr_proc; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Portal ;
typedef  TYPE_1__ PLyExecutionContext ;
typedef  TYPE_2__ PLyCursorObject ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_1__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PLy_input_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLy_input_setup_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_abort (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_begin (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_commit (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PortalIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_StopIteration ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  SPI_cursor_fetch (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_3__*) ; 
 scalar_t__ SPI_processed ; 
 TYPE_3__* SPI_tuptable ; 

__attribute__((used)) static PyObject *
PLy_cursor_iternext(PyObject *self)
{
	PLyCursorObject *cursor;
	PyObject   *ret;
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();
	volatile MemoryContext oldcontext;
	volatile ResourceOwner oldowner;
	Portal		portal;

	cursor = (PLyCursorObject *) self;

	if (cursor->closed)
	{
		PLy_exception_set(PyExc_ValueError, "iterating a closed cursor");
		return NULL;
	}

	portal = GetPortalByName(cursor->portalname);
	if (!PortalIsValid(portal))
	{
		PLy_exception_set(PyExc_ValueError,
						  "iterating a cursor in an aborted subtransaction");
		return NULL;
	}

	oldcontext = CurrentMemoryContext;
	oldowner = CurrentResourceOwner;

	PLy_spi_subtransaction_begin(oldcontext, oldowner);

	PG_TRY();
	{
		SPI_cursor_fetch(portal, true, 1);
		if (SPI_processed == 0)
		{
			PyErr_SetNone(PyExc_StopIteration);
			ret = NULL;
		}
		else
		{
			PLy_input_setup_tuple(&cursor->result, SPI_tuptable->tupdesc,
								  exec_ctx->curr_proc);

			ret = PLy_input_from_tuple(&cursor->result, SPI_tuptable->vals[0],
									   SPI_tuptable->tupdesc, true);
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

	return ret;
}