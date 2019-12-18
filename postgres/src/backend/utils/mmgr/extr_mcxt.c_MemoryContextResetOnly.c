#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int isReset; TYPE_1__* methods; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;} ;
typedef  TYPE_2__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextCallResetCallbacks (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  VALGRIND_CREATE_MEMPOOL (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VALGRIND_DESTROY_MEMPOOL (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
MemoryContextResetOnly(MemoryContext context)
{
	AssertArg(MemoryContextIsValid(context));

	/* Nothing to do if no pallocs since startup or last reset */
	if (!context->isReset)
	{
		MemoryContextCallResetCallbacks(context);

		/*
		 * If context->ident points into the context's memory, it will become
		 * a dangling pointer.  We could prevent that by setting it to NULL
		 * here, but that would break valid coding patterns that keep the
		 * ident elsewhere, e.g. in a parent context.  Another idea is to use
		 * MemoryContextContains(), but we don't require ident strings to be
		 * in separately-palloc'd chunks, so that risks false positives.  So
		 * for now we assume the programmer got it right.
		 */

		context->methods->reset(context);
		context->isReset = true;
		VALGRIND_DESTROY_MEMPOOL(context);
		VALGRIND_CREATE_MEMPOOL(context, 0, false);
	}
}