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
 int /*<<< orphan*/  EXTI_PVD_OUTPUT ; 
 int /*<<< orphan*/  Handle_EXTI_Irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVD_IRQn ; 

void PVD_IRQHandler(void) {
    IRQ_ENTER(PVD_IRQn);
    Handle_EXTI_Irq(EXTI_PVD_OUTPUT);
    IRQ_EXIT(PVD_IRQn);
}