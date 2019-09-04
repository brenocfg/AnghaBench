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
 int MICROPY_HW_USB_MAIN_DEV ; 

__attribute__((used)) static int pyb_usbdd_detect_port(void) {
    #if MBOOT_USB_AUTODETECT_PORT
    mp_hal_pin_config(pin_A11, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_UP, 0);
    mp_hal_pin_config(pin_A12, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_UP, 0);
    int state = mp_hal_pin_read(pin_A11) == 0 && mp_hal_pin_read(pin_A12) == 0;
    mp_hal_pin_config(pin_A11, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_NONE, 0);
    mp_hal_pin_config(pin_A12, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_NONE, 0);
    if (state) {
        return USB_PHY_FS_ID;
    }
    mp_hal_pin_config(pin_B14, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_UP, 0);
    mp_hal_pin_config(pin_B15, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_UP, 0);
    state = mp_hal_pin_read(pin_B14) == 0 && mp_hal_pin_read(pin_B15) == 0;
    mp_hal_pin_config(pin_B14, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_NONE, 0);
    mp_hal_pin_config(pin_B15, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_NONE, 0);
    if (state) {
        return USB_PHY_HS_ID;
    }
    #endif
    return MICROPY_HW_USB_MAIN_DEV;
}