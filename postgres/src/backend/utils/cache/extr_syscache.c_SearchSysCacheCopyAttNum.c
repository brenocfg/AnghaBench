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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCacheAttNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 

HeapTuple
SearchSysCacheCopyAttNum(Oid relid, int16 attnum)
{
	HeapTuple	tuple,
				newtuple;

	tuple = SearchSysCacheAttNum(relid, attnum);
	if (!HeapTupleIsValid(tuple))
		return NULL;
	newtuple = heap_copytuple(tuple);
	ReleaseSysCache(tuple);
	return newtuple;
}