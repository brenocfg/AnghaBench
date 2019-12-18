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
struct ct_timer_instance {scalar_t__ running; scalar_t__ position; TYPE_2__* timer_base; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* prepare ) (struct ct_timer_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ct_timer_instance*) ; 

void ct_timer_prepare(struct ct_timer_instance *ti)
{
	if (ti->timer_base->ops->prepare)
		ti->timer_base->ops->prepare(ti);
	ti->position = 0;
	ti->running = 0;
}