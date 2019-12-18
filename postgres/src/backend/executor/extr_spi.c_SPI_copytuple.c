#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  savedcxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ERROR_ARGUMENT ; 
 int /*<<< orphan*/  SPI_ERROR_UNCONNECTED ; 
 int /*<<< orphan*/  SPI_result ; 
 TYPE_1__* _SPI_current ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 

HeapTuple
SPI_copytuple(HeapTuple tuple)
{
	MemoryContext oldcxt;
	HeapTuple	ctuple;

	if (tuple == NULL)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	if (_SPI_current == NULL)
	{
		SPI_result = SPI_ERROR_UNCONNECTED;
		return NULL;
	}

	oldcxt = MemoryContextSwitchTo(_SPI_current->savedcxt);

	ctuple = heap_copytuple(tuple);

	MemoryContextSwitchTo(oldcxt);

	return ctuple;
}