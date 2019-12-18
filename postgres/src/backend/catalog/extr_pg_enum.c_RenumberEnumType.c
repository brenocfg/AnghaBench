#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int float4 ;
struct TYPE_10__ {int enumsortorder; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 TYPE_1__* heap_copytuple (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 

__attribute__((used)) static void
RenumberEnumType(Relation pg_enum, HeapTuple *existing, int nelems)
{
	int			i;

	/*
	 * We should only need to increase existing elements' enumsortorders,
	 * never decrease them.  Therefore, work from the end backwards, to avoid
	 * unwanted uniqueness violations.
	 */
	for (i = nelems - 1; i >= 0; i--)
	{
		HeapTuple	newtup;
		Form_pg_enum en;
		float4		newsortorder;

		newtup = heap_copytuple(existing[i]);
		en = (Form_pg_enum) GETSTRUCT(newtup);

		newsortorder = i + 1;
		if (en->enumsortorder != newsortorder)
		{
			en->enumsortorder = newsortorder;

			CatalogTupleUpdate(pg_enum, &newtup->t_self, newtup);
		}

		heap_freetuple(newtup);
	}

	/* Make the updates visible */
	CommandCounterIncrement();
}