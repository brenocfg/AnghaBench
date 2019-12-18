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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  curr_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_len; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_1__ HeapTupleData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PLyDict_FromTuple (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_input_setup_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLyDict_FromComposite(PLyDatumToOb *arg, Datum d)
{
	PyObject   *dict;
	HeapTupleHeader td;
	Oid			tupType;
	int32		tupTypmod;
	TupleDesc	tupdesc;
	HeapTupleData tmptup;

	td = DatumGetHeapTupleHeader(d);
	/* Extract rowtype info and find a tupdesc */
	tupType = HeapTupleHeaderGetTypeId(td);
	tupTypmod = HeapTupleHeaderGetTypMod(td);
	tupdesc = lookup_rowtype_tupdesc(tupType, tupTypmod);

	/* Set up I/O funcs if not done yet */
	PLy_input_setup_tuple(arg, tupdesc,
						  PLy_current_execution_context()->curr_proc);

	/* Build a temporary HeapTuple control structure */
	tmptup.t_len = HeapTupleHeaderGetDatumLength(td);
	tmptup.t_data = td;

	dict = PLyDict_FromTuple(arg, &tmptup, tupdesc, true);

	ReleaseTupleDesc(tupdesc);

	return dict;
}