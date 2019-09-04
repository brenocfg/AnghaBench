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
struct TYPE_2__ {int /*<<< orphan*/  buffer_disabled; } ;

/* Variables and functions */
 TYPE_1__ global_trace ; 
 int /*<<< orphan*/  smp_rmb () ; 

int tracing_is_enabled(void)
{
	/*
	 * For quick access (irqsoff uses this in fast path), just
	 * return the mirror variable of the state of the ring buffer.
	 * It's a little racy, but we don't really care.
	 */
	smp_rmb();
	return !global_trace.buffer_disabled;
}