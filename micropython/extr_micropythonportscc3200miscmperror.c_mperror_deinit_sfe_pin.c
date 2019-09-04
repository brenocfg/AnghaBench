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
 int /*<<< orphan*/  MAP_PinConfigSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MICROPY_SAFE_BOOT_PIN_NUM ; 
 int /*<<< orphan*/  PIN_STRENGTH_4MA ; 
 int /*<<< orphan*/  PIN_TYPE_STD ; 

void mperror_deinit_sfe_pin (void) {
    // disable the pull-down
    MAP_PinConfigSet(MICROPY_SAFE_BOOT_PIN_NUM, PIN_STRENGTH_4MA, PIN_TYPE_STD);
}