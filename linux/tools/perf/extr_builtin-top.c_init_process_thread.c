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
struct TYPE_2__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * data; int /*<<< orphan*/ * in; } ;
struct perf_top {TYPE_1__ qe; } ;

/* Variables and functions */
 int /*<<< orphan*/  deliver_event ; 
 int /*<<< orphan*/  ordered_events__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_top*) ; 
 int /*<<< orphan*/  ordered_events__set_copy_on_queue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_process_thread(struct perf_top *top)
{
	ordered_events__init(&top->qe.data[0], deliver_event, top);
	ordered_events__init(&top->qe.data[1], deliver_event, top);
	ordered_events__set_copy_on_queue(&top->qe.data[0], true);
	ordered_events__set_copy_on_queue(&top->qe.data[1], true);
	top->qe.in = &top->qe.data[0];
	pthread_mutex_init(&top->qe.mutex, NULL);
	pthread_cond_init(&top->qe.cond, NULL);
}