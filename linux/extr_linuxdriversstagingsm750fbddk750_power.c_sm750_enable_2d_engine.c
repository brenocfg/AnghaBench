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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_GATE ; 
 int CURRENT_GATE_CSC ; 
 int CURRENT_GATE_DE ; 
 int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm750_set_current_gate (int) ; 

void sm750_enable_2d_engine(unsigned int enable)
{
	u32 gate;

	gate = peek32(CURRENT_GATE);
	if (enable)
		gate |= (CURRENT_GATE_DE | CURRENT_GATE_CSC);
	else
		gate &= ~(CURRENT_GATE_DE | CURRENT_GATE_CSC);

	sm750_set_current_gate(gate);
}