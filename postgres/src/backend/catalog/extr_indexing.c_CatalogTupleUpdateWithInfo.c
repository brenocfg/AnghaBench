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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogIndexInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_heap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CatalogTupleUpdateWithInfo(Relation heapRel, ItemPointer otid, HeapTuple tup,
						   CatalogIndexState indstate)
{
	simple_heap_update(heapRel, otid, tup);

	CatalogIndexInsert(indstate, tup);
}