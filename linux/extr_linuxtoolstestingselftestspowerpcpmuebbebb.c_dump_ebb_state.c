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
struct TYPE_2__ {int /*<<< orphan*/  trace; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_ebb_hw_state () ; 
 int /*<<< orphan*/  dump_summary_ebb_state () ; 
 TYPE_1__ ebb_state ; 
 int /*<<< orphan*/  trace_buffer_print (int /*<<< orphan*/ ) ; 

void dump_ebb_state(void)
{
	dump_summary_ebb_state();

	dump_ebb_hw_state();

	trace_buffer_print(ebb_state.trace);
}