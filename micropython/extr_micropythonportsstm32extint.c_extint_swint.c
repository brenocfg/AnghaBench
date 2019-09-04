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
typedef  int uint ;
struct TYPE_2__ {int SWIER; } ;

/* Variables and functions */
 TYPE_1__* EXTI ; 
 int EXTI_NUM_VECTORS ; 

void extint_swint(uint line) {
    if (line >= EXTI_NUM_VECTORS) {
        return;
    }
    // we need 0 to 1 transition to trigger the interrupt
#if defined(STM32L4) || defined(STM32H7)
    EXTI->SWIER1 &= ~(1 << line);
    EXTI->SWIER1 |= (1 << line);
#else
    EXTI->SWIER &= ~(1 << line);
    EXTI->SWIER |= (1 << line);
#endif
}