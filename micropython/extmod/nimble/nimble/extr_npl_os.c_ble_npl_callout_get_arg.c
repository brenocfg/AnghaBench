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
struct ble_npl_callout {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CALLOUT_printf (char*,struct ble_npl_callout*) ; 
 void* ble_npl_event_get_arg (int /*<<< orphan*/ *) ; 

void *ble_npl_callout_get_arg(struct ble_npl_callout *c) {
    DEBUG_CALLOUT_printf("ble_npl_callout_get_arg(%p)\n", c);
    return ble_npl_event_get_arg(&c->ev);
}