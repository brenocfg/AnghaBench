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
struct timer_pool {int running; int /*<<< orphan*/  timer; TYPE_2__* ra; } ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* timer_start ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void timer_pool_start(struct timer_pool *pool)
{
    if (!pool)
        return;

    assert(!pool->running);
    pool->ra->fns->timer_start(pool->ra, pool->timer);
    pool->running = true;
}