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
 int /*<<< orphan*/  TIMER_CTRL ; 
 int interval ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void timer_init ( void )
{
	// Set value, enable Timer and Interrupt
	put32(TIMER_CTRL, ((1<<28) | interval));
}