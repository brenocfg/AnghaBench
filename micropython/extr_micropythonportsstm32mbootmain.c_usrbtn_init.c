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
 int /*<<< orphan*/  MICROPY_HW_USRSW_PIN ; 
 int /*<<< orphan*/  MICROPY_HW_USRSW_PULL ; 
 int /*<<< orphan*/  MP_HAL_PIN_MODE_INPUT ; 
 int /*<<< orphan*/  mp_hal_pin_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usrbtn_init(void) {
    mp_hal_pin_config(MICROPY_HW_USRSW_PIN, MP_HAL_PIN_MODE_INPUT, MICROPY_HW_USRSW_PULL, 0);
}