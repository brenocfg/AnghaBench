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
 int /*<<< orphan*/  FUNC_GPIO0 ; 
 int /*<<< orphan*/  FUNC_GPIO2 ; 
 int /*<<< orphan*/  FUNC_GPIO4 ; 
 int /*<<< orphan*/  FUNC_GPIO5 ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO0_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO2_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO4_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO5_U ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_pin_mux(int pin) {
    // The API only supports setting PERIPHS_IO_MUX on GPIO 0, 2, 4, 5
    switch (pin) {
    case 0:
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
        break;
    case 2:
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
        break;
    case 4:
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
        break;
    case 5:
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
        break;
    default:
        break;
    }
}