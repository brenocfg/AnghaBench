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
struct ble_npl_callout {scalar_t__ ticks; } ;
typedef  scalar_t__ ble_npl_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CALLOUT_printf (char*,struct ble_npl_callout*,int /*<<< orphan*/ ) ; 

ble_npl_time_t ble_npl_callout_remaining_ticks(struct ble_npl_callout *c, ble_npl_time_t now) {
    DEBUG_CALLOUT_printf("ble_npl_callout_remaining_ticks(%p, %u)\n", c, (uint)now);
    if (c->ticks > now) {
        return c->ticks - now;
    } else {
        return 0;
    }
}