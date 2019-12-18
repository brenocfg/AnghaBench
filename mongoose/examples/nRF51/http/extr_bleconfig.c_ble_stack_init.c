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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NRF_CLOCK_LFCLKSRC_XTAL_20_PPM ; 
 int /*<<< orphan*/  SOFTDEVICE_HANDLER_APPSH_INIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ble_evt_dispatch ; 
 int /*<<< orphan*/  softdevice_ble_evt_handler_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ble_stack_init(void)
{
  uint32_t err_code;

  // Initialize the SoftDevice handler module.
  SOFTDEVICE_HANDLER_APPSH_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, true);

  // Register with the SoftDevice handler module for BLE events.
  err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
  APP_ERROR_CHECK(err_code);
}