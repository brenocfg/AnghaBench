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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_GATE ; 
 int /*<<< orphan*/  CURRENT_GATE_GPIO ; 
 int /*<<< orphan*/  peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_set_current_gate (int /*<<< orphan*/ ) ; 

void sm750_enable_gpio(unsigned int enable)
{
	u32 gate;

	/* Enable GPIO Gate */
	gate = peek32(CURRENT_GATE);
	if (enable)
		gate |= CURRENT_GATE_GPIO;
	else
		gate &= ~CURRENT_GATE_GPIO;

	sm750_set_current_gate(gate);
}