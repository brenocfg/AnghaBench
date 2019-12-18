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
struct trace_array {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_stub ; 

void ftrace_reset_array_ops(struct trace_array *tr)
{
	tr->ops->func = ftrace_stub;
}