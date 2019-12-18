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
 int /*<<< orphan*/  buffers_allocated ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 

void trace_printk_start_comm(void)
{
	/* Start tracing comms if trace printk is set */
	if (!buffers_allocated)
		return;
	tracing_start_cmdline_record();
}