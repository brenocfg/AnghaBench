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
struct coro {int yield_value; TYPE_1__* switcher; } ;
struct TYPE_2__ {int /*<<< orphan*/  caller; int /*<<< orphan*/  callee; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct coro*) ; 
 int /*<<< orphan*/  coro_swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

inline int coro_yield(struct coro *coro, int value)
{
    assert(coro);
    coro->yield_value = value;
    coro_swapcontext(&coro->switcher->callee, &coro->switcher->caller);
    return coro->yield_value;
}