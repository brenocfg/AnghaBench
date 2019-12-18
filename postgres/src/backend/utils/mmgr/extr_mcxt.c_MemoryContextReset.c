#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  isReset; int /*<<< orphan*/ * firstchild; } ;
typedef  TYPE_1__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDeleteChildren (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextResetOnly (TYPE_1__*) ; 

void
MemoryContextReset(MemoryContext context)
{
	AssertArg(MemoryContextIsValid(context));

	/* save a function call in common case where there are no children */
	if (context->firstchild != NULL)
		MemoryContextDeleteChildren(context);

	/* save a function call if no pallocs since startup or last reset */
	if (!context->isReset)
		MemoryContextResetOnly(context);
}