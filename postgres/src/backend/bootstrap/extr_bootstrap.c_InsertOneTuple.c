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
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTupleDesc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int* Nulls ; 
 int /*<<< orphan*/  attrtypes ; 
 int /*<<< orphan*/  boot_reldesc ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int numattr ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_heap_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  values ; 

void
InsertOneTuple(void)
{
	HeapTuple	tuple;
	TupleDesc	tupDesc;
	int			i;

	elog(DEBUG4, "inserting row with %d columns", numattr);

	tupDesc = CreateTupleDesc(numattr, attrtypes);
	tuple = heap_form_tuple(tupDesc, values, Nulls);
	pfree(tupDesc);				/* just free's tupDesc, not the attrtypes */

	simple_heap_insert(boot_reldesc, tuple);
	heap_freetuple(tuple);
	elog(DEBUG4, "row inserted");

	/*
	 * Reset null markers for next tuple
	 */
	for (i = 0; i < numattr; i++)
		Nulls[i] = false;
}