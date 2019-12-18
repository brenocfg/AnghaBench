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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,scalar_t__,int*) ; 

Datum
ExecGetJunkAttribute(TupleTableSlot *slot, AttrNumber attno,
					 bool *isNull)
{
	Assert(attno > 0);

	return slot_getattr(slot, attno, isNull);
}