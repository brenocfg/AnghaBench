#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* reset_cbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;struct TYPE_4__* next; } ;
typedef  TYPE_1__ MemoryContextCallback ;
typedef  TYPE_2__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MemoryContextCallResetCallbacks(MemoryContext context)
{
	MemoryContextCallback *cb;

	/*
	 * We pop each callback from the list before calling.  That way, if an
	 * error occurs inside the callback, we won't try to call it a second time
	 * in the likely event that we reset or delete the context later.
	 */
	while ((cb = context->reset_cbs) != NULL)
	{
		context->reset_cbs = cb->next;
		cb->func(cb->arg);
	}
}