#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  mp_uint_t ;
struct TYPE_4__ {int IMR1; int EMR1; int IMR; int EMR; } ;
struct TYPE_3__ {int IMR1; int EMR1; } ;

/* Variables and functions */
 TYPE_2__* EXTI ; 
 TYPE_1__* EXTI_D1 ; 
 scalar_t__ EXTI_MODE_BB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXTI_Mode_Event ; 
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 int EXTI_NUM_VECTORS ; 
 int /*<<< orphan*/  disable_irq () ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

void extint_disable(uint line) {
    if (line >= EXTI_NUM_VECTORS) {
        return;
    }

    #if !defined(EXTI_MODE_BB)
    // This MCU doesn't have bitband support.
    mp_uint_t irq_state = disable_irq();
    #if defined(STM32H7)
    EXTI_D1->IMR1 &= ~(1 << line);
    EXTI_D1->EMR1 &= ~(1 << line);
    #elif defined(STM32WB)
    EXTI->IMR1 &= ~(1 << line);
    EXTI->EMR1 &= ~(1 << line);
    #else
    EXTI->IMR &= ~(1 << line);
    EXTI->EMR &= ~(1 << line);
    #endif
    enable_irq(irq_state);
    #else
    // Since manipulating IMR/EMR is a read-modify-write, and we want this to
    // be atomic, we use the bit-band area to just affect the bit we're
    // interested in.
    EXTI_MODE_BB(EXTI_Mode_Interrupt, line) = 0;
    EXTI_MODE_BB(EXTI_Mode_Event, line) = 0;
    #endif
}