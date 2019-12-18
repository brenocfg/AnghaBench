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
 int /*<<< orphan*/  SysTick_Config (int) ; 
 int SystemCoreClock ; 
 scalar_t__ timer_count ; 

void timer_init(void) {
    timer_count = 0;
    SysTick_Config(SystemCoreClock / 1000); /* 1ms tick */
}