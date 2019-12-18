#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numbers_arr; scalar_t__ values_arr; scalar_t__ values; } ;
typedef  TYPE_1__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (scalar_t__) ; 

void
free_attstatsslot(AttStatsSlot *sslot)
{
	/* The values[] array was separately palloc'd by deconstruct_array */
	if (sslot->values)
		pfree(sslot->values);
	/* The numbers[] array points into numbers_arr, do not pfree it */
	/* Free the detoasted array objects, if any */
	if (sslot->values_arr)
		pfree(sslot->values_arr);
	if (sslot->numbers_arr)
		pfree(sslot->numbers_arr);
}