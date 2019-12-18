#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oldowner; int /*<<< orphan*/  oldcontext; } ;
struct TYPE_4__ {int exited; int /*<<< orphan*/  started; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLySubtransactionObject ;
typedef  TYPE_2__ PLySubtransactionData ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  ReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 scalar_t__ explicit_subtransactions ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static PyObject *
PLy_subtransaction_exit(PyObject *self, PyObject *args)
{
	PyObject   *type;
	PyObject   *value;
	PyObject   *traceback;
	PLySubtransactionData *subxactdata;
	PLySubtransactionObject *subxact = (PLySubtransactionObject *) self;

	if (!PyArg_ParseTuple(args, "OOO", &type, &value, &traceback))
		return NULL;

	if (!subxact->started)
	{
		PLy_exception_set(PyExc_ValueError, "this subtransaction has not been entered");
		return NULL;
	}

	if (subxact->exited)
	{
		PLy_exception_set(PyExc_ValueError, "this subtransaction has already been exited");
		return NULL;
	}

	if (explicit_subtransactions == NIL)
	{
		PLy_exception_set(PyExc_ValueError, "there is no subtransaction to exit from");
		return NULL;
	}

	subxact->exited = true;

	if (type != Py_None)
	{
		/* Abort the inner transaction */
		RollbackAndReleaseCurrentSubTransaction();
	}
	else
	{
		ReleaseCurrentSubTransaction();
	}

	subxactdata = (PLySubtransactionData *) linitial(explicit_subtransactions);
	explicit_subtransactions = list_delete_first(explicit_subtransactions);

	MemoryContextSwitchTo(subxactdata->oldcontext);
	CurrentResourceOwner = subxactdata->oldowner;
	pfree(subxactdata);

	Py_RETURN_NONE;
}