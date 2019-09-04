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

/* Variables and functions */
#define  GPIO_MODE_INPUT 130 
#define  GPIO_MODE_OPEN_DRAIN 129 
#define  GPIO_MODE_OUTPUT 128 
 int /*<<< orphan*/  PAD_XPD_DCDC_CONF ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_GPIO_CONF ; 
 int /*<<< orphan*/  RTC_GPIO_ENABLE ; 
 int /*<<< orphan*/  RTC_GPIO_OUT ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_output_set (int,int,int,int) ; 
 int* pin_mode ; 

void pin_set(uint pin, int value) {
    if (pin == 16) {
        int out_en = (pin_mode[pin] == GPIO_MODE_OUTPUT);
        WRITE_PERI_REG(PAD_XPD_DCDC_CONF, (READ_PERI_REG(PAD_XPD_DCDC_CONF) & 0xffffffbc) | 1);
        WRITE_PERI_REG(RTC_GPIO_CONF, READ_PERI_REG(RTC_GPIO_CONF) & ~1);
        WRITE_PERI_REG(RTC_GPIO_ENABLE, (READ_PERI_REG(RTC_GPIO_ENABLE) & ~1) | out_en);
        WRITE_PERI_REG(RTC_GPIO_OUT, (READ_PERI_REG(RTC_GPIO_OUT) & ~1) | value);
        return;
    }

    uint32_t enable = 0;
    uint32_t disable = 0;
    switch (pin_mode[pin]) {
        case GPIO_MODE_INPUT:
            value = -1;
            disable = 1;
            break;

        case GPIO_MODE_OUTPUT:
            enable = 1;
            break;

        case GPIO_MODE_OPEN_DRAIN:
            if (value == -1) {
                return;
            } else if (value == 0) {
                enable = 1;
            } else {
                value = -1;
                disable = 1;
            }
            break;
    }

    enable <<= pin;
    disable <<= pin;
    if (value == -1) {
        gpio_output_set(0, 0, enable, disable);
    } else {
        gpio_output_set(value << pin, (1 - value) << pin, enable, disable);
    }
}