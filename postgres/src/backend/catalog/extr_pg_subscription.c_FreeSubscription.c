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
struct TYPE_4__ {int /*<<< orphan*/  publications; struct TYPE_4__* slotname; struct TYPE_4__* conninfo; struct TYPE_4__* name; } ;
typedef  TYPE_1__ Subscription ;

/* Variables and functions */
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
FreeSubscription(Subscription *sub)
{
	pfree(sub->name);
	pfree(sub->conninfo);
	if (sub->slotname)
		pfree(sub->slotname);
	list_free_deep(sub->publications);
	pfree(sub);
}