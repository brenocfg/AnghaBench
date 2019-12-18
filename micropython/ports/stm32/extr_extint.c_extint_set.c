#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t pin; int /*<<< orphan*/  gpio; } ;
typedef  TYPE_1__ pin_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_6__ {int* EXTICR; } ;

/* Variables and functions */
 int EXTI_FTSR ; 
 int /*<<< orphan*/  EXTI_Mode_Event ; 
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 int EXTI_RTSR ; 
 scalar_t__ GPIO_GET_INDEX (int /*<<< orphan*/ ) ; 
 size_t GPIO_MODE_IT_FALLING ; 
 size_t GPIO_MODE_IT_RISING ; 
 int /*<<< orphan*/  HAL_NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PRI_EXTINT ; 
 int /*<<< orphan*/  IRQn_NONNEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__ const*) ; 
 int /*<<< orphan*/  MP_OBJ_SENTINEL ; 
 int /*<<< orphan*/ * MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* SYSCFG ; 
 int /*<<< orphan*/  __HAL_RCC_SYSCFG_CLK_ENABLE () ; 
 int /*<<< orphan*/  extint_disable (size_t) ; 
 int /*<<< orphan*/  extint_enable (size_t) ; 
 int /*<<< orphan*/ * nvic_irq_channel ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 int /*<<< orphan*/ * pyb_extint_callback_arg ; 
 int* pyb_extint_hard_irq ; 
 int /*<<< orphan*/ * pyb_extint_mode ; 

void extint_set(const pin_obj_t *pin, uint32_t mode) {
    uint32_t line = pin->pin;

    mp_obj_t *cb = &MP_STATE_PORT(pyb_extint_callback)[line];

    extint_disable(line);

    *cb = MP_OBJ_SENTINEL;

    pyb_extint_mode[line] = (mode & 0x00010000) ? // GPIO_MODE_IT == 0x00010000
        EXTI_Mode_Interrupt : EXTI_Mode_Event;

    {
        // Configure and enable the callback

        pyb_extint_hard_irq[line] = 1;
        pyb_extint_callback_arg[line] = MP_OBJ_FROM_PTR(pin);

        // Route the GPIO to EXTI
        #if !defined(STM32WB)
        __HAL_RCC_SYSCFG_CLK_ENABLE();
        #endif
        SYSCFG->EXTICR[line >> 2] =
            (SYSCFG->EXTICR[line >> 2] & ~(0x0f << (4 * (line & 0x03))))
            | ((uint32_t)(GPIO_GET_INDEX(pin->gpio)) << (4 * (line & 0x03)));

        // Enable or disable the rising detector
        if ((mode & GPIO_MODE_IT_RISING) == GPIO_MODE_IT_RISING) {
            EXTI_RTSR |= 1 << line;
        } else {
            EXTI_RTSR &= ~(1 << line);
        }

        // Enable or disable the falling detector
        if ((mode & GPIO_MODE_IT_FALLING) == GPIO_MODE_IT_FALLING) {
            EXTI_FTSR |= 1 << line;
        } else {
            EXTI_FTSR &= ~(1 << line);
        }

        // Configure the NVIC
        NVIC_SetPriority(IRQn_NONNEG(nvic_irq_channel[line]), IRQ_PRI_EXTINT);
        HAL_NVIC_EnableIRQ(nvic_irq_channel[line]);

        // Enable the interrupt
        extint_enable(line);
    }
}