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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  trace_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_ftrace_now (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ global_trace ; 

u64 ftrace_now(int cpu)
{
	return buffer_ftrace_now(&global_trace.trace_buffer, cpu);
}