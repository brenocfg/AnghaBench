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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ ble_npl_time_t ;
typedef  int /*<<< orphan*/  ble_npl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_NPL_OK ; 
 int /*<<< orphan*/  DEBUG_TIME_printf (char*,int /*<<< orphan*/ ) ; 

ble_npl_error_t ble_npl_time_ms_to_ticks(uint32_t ms, ble_npl_time_t *out_ticks) {
    DEBUG_TIME_printf("ble_npl_time_ms_to_ticks(%u)\n", (uint)ms);
    *out_ticks = ms;
    return BLE_NPL_OK;
}