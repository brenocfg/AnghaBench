#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_4__* TupleDesc ;
struct TYPE_22__ {scalar_t__ tupdescid; scalar_t__ natts; TYPE_4__* recdesc; TYPE_1__* typentry; } ;
struct TYPE_23__ {TYPE_2__ tuple; } ;
struct TYPE_25__ {scalar_t__ typoid; TYPE_3__ u; int /*<<< orphan*/  typmod; } ;
struct TYPE_24__ {scalar_t__ natts; } ;
struct TYPE_21__ {scalar_t__ tupDesc_identifier; TYPE_4__* tupDesc; } ;
struct TYPE_20__ {int /*<<< orphan*/  curr_proc; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_5__ PLyObToDatum ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PLyGenericObject_ToComposite (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PLyMapping_ToComposite (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLySequence_ToComposite (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLyString_ToComposite (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 TYPE_11__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_output_setup_tuple (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PinTupleDesc (TYPE_4__*) ; 
 scalar_t__ PyMapping_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySequence_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_4__*) ; 
 TYPE_4__* lookup_rowtype_tupdesc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
PLyObject_ToComposite(PLyObToDatum *arg, PyObject *plrv,
					  bool *isnull, bool inarray)
{
	Datum		rv;
	TupleDesc	desc;

	if (plrv == Py_None)
	{
		*isnull = true;
		return (Datum) 0;
	}
	*isnull = false;

	/*
	 * The string conversion case doesn't require a tupdesc, nor per-field
	 * conversion data, so just go for it if that's the case to use.
	 */
	if (PyString_Check(plrv) || PyUnicode_Check(plrv))
		return PLyString_ToComposite(arg, plrv, inarray);

	/*
	 * If we're dealing with a named composite type, we must look up the
	 * tupdesc every time, to protect against possible changes to the type.
	 * RECORD types can't change between calls; but we must still be willing
	 * to set up the info the first time, if nobody did yet.
	 */
	if (arg->typoid != RECORDOID)
	{
		desc = lookup_rowtype_tupdesc(arg->typoid, arg->typmod);
		/* We should have the descriptor of the type's typcache entry */
		Assert(desc == arg->u.tuple.typentry->tupDesc);
		/* Detect change of descriptor, update cache if needed */
		if (arg->u.tuple.tupdescid != arg->u.tuple.typentry->tupDesc_identifier)
		{
			PLy_output_setup_tuple(arg, desc,
								   PLy_current_execution_context()->curr_proc);
			arg->u.tuple.tupdescid = arg->u.tuple.typentry->tupDesc_identifier;
		}
	}
	else
	{
		desc = arg->u.tuple.recdesc;
		if (desc == NULL)
		{
			desc = lookup_rowtype_tupdesc(arg->typoid, arg->typmod);
			arg->u.tuple.recdesc = desc;
		}
		else
		{
			/* Pin descriptor to match unpin below */
			PinTupleDesc(desc);
		}
	}

	/* Simple sanity check on our caching */
	Assert(desc->natts == arg->u.tuple.natts);

	/*
	 * Convert, using the appropriate method depending on the type of the
	 * supplied Python object.
	 */
	if (PySequence_Check(plrv))
		/* composite type as sequence (tuple, list etc) */
		rv = PLySequence_ToComposite(arg, desc, plrv);
	else if (PyMapping_Check(plrv))
		/* composite type as mapping (currently only dict) */
		rv = PLyMapping_ToComposite(arg, desc, plrv);
	else
		/* returned as smth, must provide method __getattr__(name) */
		rv = PLyGenericObject_ToComposite(arg, desc, plrv, inarray);

	ReleaseTupleDesc(desc);

	return rv;
}