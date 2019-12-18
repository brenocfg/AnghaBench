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
struct TYPE_4__ {int /*<<< orphan*/  obj; struct TYPE_4__* next; scalar_t__ ref; } ;
typedef  TYPE_1__ scope_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

void scope_release(scope_chain_t *scope)
{
    if(--scope->ref)
        return;

    if(scope->next)
        scope_release(scope->next);

    IDispatch_Release(scope->obj);
    heap_free(scope);
}