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
struct srp_event_struct {TYPE_1__* hostdata; int /*<<< orphan*/  free; } ;
struct event_pool {int /*<<< orphan*/  events; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct srp_event_struct*,...) ; 
 int /*<<< orphan*/  valid_event_struct (struct event_pool*,struct srp_event_struct*) ; 

__attribute__((used)) static void free_event_struct(struct event_pool *pool,
				       struct srp_event_struct *evt)
{
	if (!valid_event_struct(pool, evt)) {
		dev_err(evt->hostdata->dev, "Freeing invalid event_struct %p "
			"(not in pool %p)\n", evt, pool->events);
		return;
	}
	if (atomic_inc_return(&evt->free) != 1) {
		dev_err(evt->hostdata->dev, "Freeing event_struct %p "
			"which is not in use!\n", evt);
		return;
	}
}