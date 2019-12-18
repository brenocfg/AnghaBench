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
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_output (struct perf_event*,struct perf_sample_data*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_output_begin_forward ; 

void
perf_event_output_forward(struct perf_event *event,
			 struct perf_sample_data *data,
			 struct pt_regs *regs)
{
	__perf_event_output(event, data, regs, perf_output_begin_forward);
}