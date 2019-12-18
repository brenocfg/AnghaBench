#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lwan_array {size_t elements; struct coro_defer* base; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct coro_defer {TYPE_2__ one; TYPE_1__ two; scalar_t__ has_two_args; } ;
struct coro {int /*<<< orphan*/  defer; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void coro_deferred_run(struct coro *coro, size_t generation)
{
    struct lwan_array *array = (struct lwan_array *)&coro->defer;
    struct coro_defer *defers = array->base;

    for (size_t i = array->elements; i != generation; i--) {
        struct coro_defer *defer = &defers[i - 1];

        if (defer->has_two_args)
            defer->two.func(defer->two.data1, defer->two.data2);
        else
            defer->one.func(defer->one.data);
    }

    array->elements = generation;
}