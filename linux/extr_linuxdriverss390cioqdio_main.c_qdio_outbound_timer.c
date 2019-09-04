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
struct timer_list {int dummy; } ;
struct qdio_q {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {TYPE_1__ out; } ;

/* Variables and functions */
 struct qdio_q* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct qdio_q* q ; 
 int /*<<< orphan*/  qdio_tasklet_schedule (struct qdio_q*) ; 
 TYPE_2__ u ; 

void qdio_outbound_timer(struct timer_list *t)
{
	struct qdio_q *q = from_timer(q, t, u.out.timer);

	qdio_tasklet_schedule(q);
}