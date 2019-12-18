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
struct TYPE_2__ {int /*<<< orphan*/  num_dead_tuples; scalar_t__ dead_tuples; } ;
typedef  TYPE_1__ LVRelStats ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;

/* Variables and functions */
 scalar_t__ bsearch (void*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vac_cmp_itemptr ; 

__attribute__((used)) static bool
lazy_tid_reaped(ItemPointer itemptr, void *state)
{
	LVRelStats *vacrelstats = (LVRelStats *) state;
	ItemPointer res;

	res = (ItemPointer) bsearch((void *) itemptr,
								(void *) vacrelstats->dead_tuples,
								vacrelstats->num_dead_tuples,
								sizeof(ItemPointerData),
								vac_cmp_itemptr);

	return (res != NULL);
}