#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int location; int length; } ;
typedef  TYPE_1__ pgssLocationLen ;
struct TYPE_6__ {int clocations_count; int clocations_buf_size; TYPE_1__* clocations; } ;
typedef  TYPE_2__ pgssJumbleState ;

/* Variables and functions */
 scalar_t__ repalloc (TYPE_1__*,int) ; 

__attribute__((used)) static void
RecordConstLocation(pgssJumbleState *jstate, int location)
{
	/* -1 indicates unknown or undefined location */
	if (location >= 0)
	{
		/* enlarge array if needed */
		if (jstate->clocations_count >= jstate->clocations_buf_size)
		{
			jstate->clocations_buf_size *= 2;
			jstate->clocations = (pgssLocationLen *)
				repalloc(jstate->clocations,
						 jstate->clocations_buf_size *
						 sizeof(pgssLocationLen));
		}
		jstate->clocations[jstate->clocations_count].location = location;
		/* initialize lengths to -1 to simplify fill_in_constant_lengths */
		jstate->clocations[jstate->clocations_count].length = -1;
		jstate->clocations_count++;
	}
}