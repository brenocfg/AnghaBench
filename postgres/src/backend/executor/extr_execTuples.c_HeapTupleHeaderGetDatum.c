#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderHasExternal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toast_flatten_tuple_to_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Datum
HeapTupleHeaderGetDatum(HeapTupleHeader tuple)
{
	Datum		result;
	TupleDesc	tupDesc;

	/* No work if there are no external TOAST pointers in the tuple */
	if (!HeapTupleHeaderHasExternal(tuple))
		return PointerGetDatum(tuple);

	/* Use the type data saved by heap_form_tuple to look up the rowtype */
	tupDesc = lookup_rowtype_tupdesc(HeapTupleHeaderGetTypeId(tuple),
									 HeapTupleHeaderGetTypMod(tuple));

	/* And do the flattening */
	result = toast_flatten_tuple_to_datum(tuple,
										  HeapTupleHeaderGetDatumLength(tuple),
										  tupDesc);

	ReleaseTupleDesc(tupDesc);

	return result;
}