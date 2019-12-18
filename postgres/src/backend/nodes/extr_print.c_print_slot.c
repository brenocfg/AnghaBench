#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;

/* Variables and functions */
 scalar_t__ TupIsNull (TYPE_1__*) ; 
 int /*<<< orphan*/  debugtup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
print_slot(TupleTableSlot *slot)
{
	if (TupIsNull(slot))
	{
		printf("tuple is null.\n");
		return;
	}
	if (!slot->tts_tupleDescriptor)
	{
		printf("no tuple descriptor.\n");
		return;
	}

	debugtup(slot, NULL);
}