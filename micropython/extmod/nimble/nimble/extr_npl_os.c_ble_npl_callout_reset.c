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
typedef  int /*<<< orphan*/  uint ;
struct ble_npl_callout {int active; scalar_t__ ticks; } ;
typedef  scalar_t__ ble_npl_time_t ;
typedef  int /*<<< orphan*/  ble_npl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_NPL_OK ; 
 int /*<<< orphan*/  DEBUG_CALLOUT_printf (char*,struct ble_npl_callout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ble_npl_time_get () ; 
 scalar_t__ mp_hal_ticks_ms () ; 

ble_npl_error_t ble_npl_callout_reset(struct ble_npl_callout *c, ble_npl_time_t ticks) {
    DEBUG_CALLOUT_printf("ble_npl_callout_reset(%p, %u) tnow=%u\n", c, (uint)ticks, (uint)mp_hal_ticks_ms());
    c->active = true;
    c->ticks = ble_npl_time_get() + ticks;
    return BLE_NPL_OK;
}