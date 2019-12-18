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
struct TYPE_3__ {int phys_port; int /*<<< orphan*/  periph; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ pyb_pin_obj_t ;
typedef  size_t mp_hal_pin_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/  PAD_XPD_DCDC_CONF ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_PULLUP_DIS (int /*<<< orphan*/ ) ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_GPIO_CONF ; 
 int /*<<< orphan*/  RTC_GPIO_ENABLE ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_output_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pin_mode ; 
 TYPE_1__* pyb_pin_obj ; 

void mp_hal_pin_output(mp_hal_pin_obj_t pin_id) {
    pin_mode[pin_id] = GPIO_MODE_OUTPUT;
    if (pin_id == 16) {
        WRITE_PERI_REG(PAD_XPD_DCDC_CONF, (READ_PERI_REG(PAD_XPD_DCDC_CONF) & 0xffffffbc) | 1);
        WRITE_PERI_REG(RTC_GPIO_CONF, READ_PERI_REG(RTC_GPIO_CONF) & ~1);
        WRITE_PERI_REG(RTC_GPIO_ENABLE, (READ_PERI_REG(RTC_GPIO_ENABLE) & ~1) | 1); // output
    } else {
        const pyb_pin_obj_t *self = &pyb_pin_obj[pin_id];
        PIN_FUNC_SELECT(self->periph, self->func);
        PIN_PULLUP_DIS(self->periph);
        gpio_output_set(0, 0, 1 << self->phys_port, 0);
    }
}