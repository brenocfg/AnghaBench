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
typedef  int uint32_t ;
typedef  int uint ;
typedef  int /*<<< orphan*/  mp_uint_t ;

/* Variables and functions */
 int EXTI_FTSR ; 
 int EXTI_MODE_BB (int /*<<< orphan*/ ,int) ; 
 int EXTI_NUM_VECTORS ; 
 int EXTI_RTSR ; 
 int /*<<< orphan*/  EXTI_Trigger_Falling ; 
 int /*<<< orphan*/  EXTI_Trigger_Rising ; 
 int GPIO_MODE_IT_FALLING ; 
 int GPIO_MODE_IT_RISING ; 
 int /*<<< orphan*/  disable_irq () ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

void extint_trigger_mode(uint line, uint32_t mode) {
    if (line >= EXTI_NUM_VECTORS) {
        return;
    }
    #if !defined(EXTI_MODE_BB)
    // This MCU doesn't have bitband support.
    mp_uint_t irq_state = disable_irq();
    // Enable or disable the rising detector
    if ((mode & GPIO_MODE_IT_RISING) == GPIO_MODE_IT_RISING) {
        EXTI_RTSR |= (1 << line);
    } else {
        EXTI_RTSR &= ~(1 << line);
    }
    // Enable or disable the falling detector
    if ((mode & GPIO_MODE_IT_FALLING) == GPIO_MODE_IT_FALLING) {
        EXTI_FTSR |= 1 << line;
    } else {
        EXTI_FTSR &= ~(1 << line);
    }
    enable_irq(irq_state);
    #else
    // Since manipulating FTSR/RTSR is a read-modify-write, and we want this to
    // be atomic, we use the bit-band area to just affect the bit we're
    // interested in.
    EXTI_MODE_BB(EXTI_Trigger_Rising, line) = (mode & GPIO_MODE_IT_RISING) == GPIO_MODE_IT_RISING;
    EXTI_MODE_BB(EXTI_Trigger_Falling, line) = (mode & GPIO_MODE_IT_FALLING) == GPIO_MODE_IT_FALLING;
    #endif
}