#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint ;
struct TYPE_5__ {int pin; int /*<<< orphan*/  gpio; int /*<<< orphan*/  pin_mask; } ;
typedef  TYPE_1__ pin_obj_t ;
typedef  scalar_t__ mp_obj_t ;
struct TYPE_6__ {int Mode; int Pull; int /*<<< orphan*/  Speed; int /*<<< orphan*/  Pin; } ;
typedef  TYPE_2__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  EXTI_Mode_Event ; 
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 int EXTI_NUM_VECTORS ; 
 int GPIO_MODE_EVT_FALLING ; 
 int GPIO_MODE_EVT_RISING ; 
 int GPIO_MODE_EVT_RISING_FALLING ; 
 int GPIO_MODE_IT_FALLING ; 
 int GPIO_MODE_IT_RISING ; 
 int GPIO_MODE_IT_RISING_FALLING ; 
 int GPIO_NOPULL ; 
 int GPIO_PULLDOWN ; 
 int GPIO_PULLUP ; 
 int /*<<< orphan*/  GPIO_SPEED_FREQ_HIGH ; 
 int /*<<< orphan*/  HAL_GPIO_Init (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HAL_NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PRI_EXTINT ; 
 int /*<<< orphan*/  IRQn_NONNEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int) ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extint_disable (int) ; 
 int /*<<< orphan*/  extint_enable (int) ; 
 int /*<<< orphan*/  extint_trigger_mode (int,int) ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  mp_hal_gpio_clock_enable (int /*<<< orphan*/ ) ; 
 int mp_obj_get_int (scalar_t__) ; 
 scalar_t__ mp_obj_is_int (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvic_irq_channel ; 
 TYPE_1__* pin_find (scalar_t__) ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 int /*<<< orphan*/ * pyb_extint_callback_arg ; 
 int* pyb_extint_hard_irq ; 
 int /*<<< orphan*/ * pyb_extint_mode ; 

uint extint_register(mp_obj_t pin_obj, uint32_t mode, uint32_t pull, mp_obj_t callback_obj, bool override_callback_obj) {
    const pin_obj_t *pin = NULL;
    uint v_line;

    if (mp_obj_is_int(pin_obj)) {
        // If an integer is passed in, then use it to identify lines 16 thru 22
        // We expect lines 0 thru 15 to be passed in as a pin, so that we can
        // get both the port number and line number.
        v_line = mp_obj_get_int(pin_obj);
        if (v_line < 16) {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "ExtInt vector %d < 16, use a Pin object", v_line));
        }
        if (v_line >= EXTI_NUM_VECTORS) {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "ExtInt vector %d >= max of %d", v_line, EXTI_NUM_VECTORS));
        }
    } else {
        pin = pin_find(pin_obj);
        v_line = pin->pin;
    }
    if (mode != GPIO_MODE_IT_RISING &&
        mode != GPIO_MODE_IT_FALLING &&
        mode != GPIO_MODE_IT_RISING_FALLING &&
        mode != GPIO_MODE_EVT_RISING &&
        mode != GPIO_MODE_EVT_FALLING &&
        mode != GPIO_MODE_EVT_RISING_FALLING) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "invalid ExtInt Mode: %d", mode));
    }
    if (pull != GPIO_NOPULL &&
        pull != GPIO_PULLUP &&
        pull != GPIO_PULLDOWN) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "invalid ExtInt Pull: %d", pull));
    }

    mp_obj_t *cb = &MP_STATE_PORT(pyb_extint_callback)[v_line];
    if (!override_callback_obj && *cb != mp_const_none && callback_obj != mp_const_none) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "ExtInt vector %d is already in use", v_line));
    }

    // We need to update callback atomically, so we disable the line
    // before we update anything.

    extint_disable(v_line);

    *cb = callback_obj;
    pyb_extint_mode[v_line] = (mode & 0x00010000) ? // GPIO_MODE_IT == 0x00010000
        EXTI_Mode_Interrupt : EXTI_Mode_Event;

    if (*cb != mp_const_none) {
        pyb_extint_hard_irq[v_line] = true;
        pyb_extint_callback_arg[v_line] = MP_OBJ_NEW_SMALL_INT(v_line);

        if (pin == NULL) {
            // pin will be NULL for non GPIO EXTI lines
            extint_trigger_mode(v_line, mode);
            extint_enable(v_line);
        } else {
            mp_hal_gpio_clock_enable(pin->gpio);
            GPIO_InitTypeDef exti;
            exti.Pin = pin->pin_mask;
            exti.Mode = mode;
            exti.Pull = pull;
            exti.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(pin->gpio, &exti);

            // Calling HAL_GPIO_Init does an implicit extint_enable
        }

        /* Enable and set NVIC Interrupt to the lowest priority */
        NVIC_SetPriority(IRQn_NONNEG(nvic_irq_channel[v_line]), IRQ_PRI_EXTINT);
        HAL_NVIC_EnableIRQ(nvic_irq_channel[v_line]);
    }
    return v_line;
}