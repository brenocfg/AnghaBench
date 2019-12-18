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
struct TYPE_4__ {scalar_t__ callback; void* arg; struct TYPE_4__* next; } ;
typedef  TYPE_1__ XactCallbackItem ;
typedef  scalar_t__ XactCallback ;

/* Variables and functions */
 TYPE_1__* Xact_callbacks ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
UnregisterXactCallback(XactCallback callback, void *arg)
{
	XactCallbackItem *item;
	XactCallbackItem *prev;

	prev = NULL;
	for (item = Xact_callbacks; item; prev = item, item = item->next)
	{
		if (item->callback == callback && item->arg == arg)
		{
			if (prev)
				prev->next = item->next;
			else
				Xact_callbacks = item->next;
			pfree(item);
			break;
		}
	}
}