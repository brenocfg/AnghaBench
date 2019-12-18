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
 int RESET_VALUE ; 
 int /*<<< orphan*/  TIMER_CS ; 
 int TIMER_EN ; 
 int TIMER_IRQ_CORE0 ; 
 int TIMER_IRQ_EN ; 
 int /*<<< orphan*/  TIMER_LIR ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void timer_init ( void )
{
	put32(TIMER_CS,  TIMER_IRQ_EN | TIMER_EN | RESET_VALUE);
	put32(TIMER_LIR, TIMER_IRQ_CORE0);
}