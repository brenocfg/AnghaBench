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
 scalar_t__ MICROPY_HW_USRSW_PRESSED ; 
 scalar_t__ mp_hal_pin_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usrbtn_state(void) {
    return mp_hal_pin_read(MICROPY_HW_USRSW_PIN) == MICROPY_HW_USRSW_PRESSED;
}