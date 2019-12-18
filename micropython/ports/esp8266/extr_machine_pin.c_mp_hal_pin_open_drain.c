#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int phys_port; int /*<<< orphan*/  func; int /*<<< orphan*/  periph; } ;
typedef  TYPE_1__ pyb_pin_obj_t ;
typedef  size_t mp_hal_pin_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETS_GPIO_INTR_DISABLE () ; 
 int /*<<< orphan*/  ETS_GPIO_INTR_ENABLE () ; 
 int /*<<< orphan*/  GPIO_ENABLE_ADDRESS ; 
 int /*<<< orphan*/  GPIO_ID_PIN (int) ; 
 int /*<<< orphan*/  GPIO_PAD_DRIVER_ENABLE ; 
 int /*<<< orphan*/  GPIO_PIN_ADDR (int /*<<< orphan*/ ) ; 
 int GPIO_PIN_PAD_DRIVER_SET (int /*<<< orphan*/ ) ; 
 int GPIO_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAD_XPD_DCDC_CONF ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_GPIO_CONF ; 
 int /*<<< orphan*/  RTC_GPIO_ENABLE ; 
 int /*<<< orphan*/  RTC_GPIO_OUT ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pyb_pin_obj ; 

void mp_hal_pin_open_drain(mp_hal_pin_obj_t pin_id) {
    const pyb_pin_obj_t *pin = &pyb_pin_obj[pin_id];

    if (pin->phys_port == 16) {
        // configure GPIO16 as input with output register holding 0
        WRITE_PERI_REG(PAD_XPD_DCDC_CONF, (READ_PERI_REG(PAD_XPD_DCDC_CONF) & 0xffffffbc) | 1);
        WRITE_PERI_REG(RTC_GPIO_CONF, READ_PERI_REG(RTC_GPIO_CONF) & ~1);
        WRITE_PERI_REG(RTC_GPIO_ENABLE, (READ_PERI_REG(RTC_GPIO_ENABLE) & ~1)); // input
        WRITE_PERI_REG(RTC_GPIO_OUT, (READ_PERI_REG(RTC_GPIO_OUT) & ~1)); // out=0
        return;
    }

    ETS_GPIO_INTR_DISABLE();
    PIN_FUNC_SELECT(pin->periph, pin->func);
    GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(pin->phys_port)),
        GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(pin->phys_port)))
        | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)); // open drain
    GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS,
        GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (1 << pin->phys_port));
    ETS_GPIO_INTR_ENABLE();
}