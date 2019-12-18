#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ExprState {TYPE_2__* parent; } ;
struct TYPE_6__ {int (* compile_expr ) (struct ExprState*) ;} ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {int es_jit_flags; } ;

/* Variables and functions */
 int PGJIT_EXPR ; 
 int PGJIT_PERFORM ; 
 TYPE_3__ provider ; 
 scalar_t__ provider_init () ; 
 int stub1 (struct ExprState*) ; 

bool
jit_compile_expr(struct ExprState *state)
{
	/*
	 * We can easily create a one-off context for functions without an
	 * associated PlanState (and thus EState). But because there's no executor
	 * shutdown callback that could deallocate the created function, they'd
	 * live to the end of the transactions, where they'd be cleaned up by the
	 * resowner machinery. That can lead to a noticeable amount of memory
	 * usage, and worse, trigger some quadratic behaviour in gdb. Therefore,
	 * at least for now, don't create a JITed function in those circumstances.
	 */
	if (!state->parent)
		return false;

	/* if no jitting should be performed at all */
	if (!(state->parent->state->es_jit_flags & PGJIT_PERFORM))
		return false;

	/* or if expressions aren't JITed */
	if (!(state->parent->state->es_jit_flags & PGJIT_EXPR))
		return false;

	/* this also takes !jit_enabled into account */
	if (provider_init())
		return provider.compile_expr(state);

	return false;
}