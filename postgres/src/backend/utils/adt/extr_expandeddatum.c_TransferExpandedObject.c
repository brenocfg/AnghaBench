#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  eoh_context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ExpandedObjectHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOHPGetRWDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 

Datum
TransferExpandedObject(Datum d, MemoryContext new_parent)
{
	ExpandedObjectHeader *eohptr = DatumGetEOHP(d);

	/* Assert caller gave a R/W pointer */
	Assert(VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(d)));

	/* Transfer ownership */
	MemoryContextSetParent(eohptr->eoh_context, new_parent);

	/* Return the object's standard read-write pointer */
	return EOHPGetRWDatum(eohptr);
}