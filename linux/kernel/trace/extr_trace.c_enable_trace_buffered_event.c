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

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_buffered_event_cnt ; 

__attribute__((used)) static void enable_trace_buffered_event(void *data)
{
	/* Probably not needed, but do it anyway */
	smp_rmb();
	this_cpu_dec(trace_buffered_event_cnt);
}