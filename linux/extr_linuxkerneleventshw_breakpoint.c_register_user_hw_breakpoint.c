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
struct task_struct {int dummy; } ;
struct perf_event_attr {int dummy; } ;
struct perf_event {int dummy; } ;
typedef  int /*<<< orphan*/  perf_overflow_handler_t ;

/* Variables and functions */
 struct perf_event* perf_event_create_kernel_counter (struct perf_event_attr*,int,struct task_struct*,int /*<<< orphan*/ ,void*) ; 

struct perf_event *
register_user_hw_breakpoint(struct perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    void *context,
			    struct task_struct *tsk)
{
	return perf_event_create_kernel_counter(attr, -1, tsk, triggered,
						context);
}