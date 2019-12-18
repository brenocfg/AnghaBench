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
struct TYPE_2__ {struct ordered_events* data; struct ordered_events* in; } ;
struct perf_top {TYPE_1__ qe; } ;
struct ordered_events {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ordered_events *rotate_queues(struct perf_top *top)
{
	struct ordered_events *in = top->qe.in;

	if (top->qe.in == &top->qe.data[1])
		top->qe.in = &top->qe.data[0];
	else
		top->qe.in = &top->qe.data[1];

	return in;
}