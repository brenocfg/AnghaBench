#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct coro {int /*<<< orphan*/  defer; int /*<<< orphan*/  vg_stack_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALGRIND_STACK_DEREGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct coro*) ; 
 int /*<<< orphan*/  coro_defer_array_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coro_deferred_run (struct coro*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct coro*) ; 

void coro_free(struct coro *coro)
{
    assert(coro);
#if !defined(NDEBUG) && defined(HAVE_VALGRIND)
    VALGRIND_STACK_DEREGISTER(coro->vg_stack_id);
#endif
    coro_deferred_run(coro, 0);
    coro_defer_array_reset(&coro->defer);
    free(coro);
}