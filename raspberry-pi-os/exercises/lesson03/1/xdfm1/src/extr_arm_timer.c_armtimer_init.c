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
 int /*<<< orphan*/  ARMTIMER_CTRL ; 
 int ARMTIMER_CTRL_23BIT ; 
 int ARMTIMER_CTRL_ENABLE ; 
 int ARMTIMER_CTRL_INT_ENABLE ; 
 int ARMTIMER_CTRL_PRESCALE256 ; 
 int /*<<< orphan*/  ARMTIMER_LOAD ; 
 int interval ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void armtimer_init ( void )
{
	put32(ARMTIMER_LOAD, interval);
	put32(ARMTIMER_CTRL, ARMTIMER_CTRL_23BIT | 
			    ARMTIMER_CTRL_PRESCALE256 |		//presclaer clk/256
			    ARMTIMER_CTRL_ENABLE |
			    ARMTIMER_CTRL_INT_ENABLE); 
}