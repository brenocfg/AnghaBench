#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  savedcxt; } ;
struct TYPE_6__ {scalar_t__ tdtypeid; scalar_t__ tdtypmod; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * HeapTupleHeader ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  SPI_ERROR_ARGUMENT ; 
 int /*<<< orphan*/  SPI_ERROR_UNCONNECTED ; 
 int /*<<< orphan*/  SPI_result ; 
 TYPE_4__* _SPI_current ; 
 int /*<<< orphan*/  assign_record_type_typmod (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_copy_tuple_as_datum (int /*<<< orphan*/ *,TYPE_1__*) ; 

HeapTupleHeader
SPI_returntuple(HeapTuple tuple, TupleDesc tupdesc)
{
	MemoryContext oldcxt;
	HeapTupleHeader dtup;

	if (tuple == NULL || tupdesc == NULL)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	if (_SPI_current == NULL)
	{
		SPI_result = SPI_ERROR_UNCONNECTED;
		return NULL;
	}

	/* For RECORD results, make sure a typmod has been assigned */
	if (tupdesc->tdtypeid == RECORDOID &&
		tupdesc->tdtypmod < 0)
		assign_record_type_typmod(tupdesc);

	oldcxt = MemoryContextSwitchTo(_SPI_current->savedcxt);

	dtup = DatumGetHeapTupleHeader(heap_copy_tuple_as_datum(tuple, tupdesc));

	MemoryContextSwitchTo(oldcxt);

	return dtup;
}