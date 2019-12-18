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
 scalar_t__ __disable_trace_on_warning ; 
 int /*<<< orphan*/  tracing_off () ; 

void disable_trace_on_warning(void)
{
	if (__disable_trace_on_warning)
		tracing_off();
}