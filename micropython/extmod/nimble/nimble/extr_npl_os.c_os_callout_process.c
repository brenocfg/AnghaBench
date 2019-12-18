#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint ;
struct TYPE_3__ {int /*<<< orphan*/  (* fn ) (TYPE_1__*) ;} ;
struct ble_npl_callout {int active; TYPE_1__ ev; scalar_t__ evq; scalar_t__ ticks; struct ble_npl_callout* nextc; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CALLOUT_printf (char*,struct ble_npl_callout*,...) ; 
 int /*<<< orphan*/  ble_npl_eventq_put (scalar_t__,TYPE_1__*) ; 
 struct ble_npl_callout* global_callout ; 
 scalar_t__ mp_hal_ticks_ms () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void os_callout_process(void) {
    uint32_t tnow = mp_hal_ticks_ms();
    for (struct ble_npl_callout *c = global_callout; c != NULL; c = c->nextc) {
        if (!c->active) {
            continue;
        }
        if ((int32_t)(tnow - c->ticks) >= 0) {
            DEBUG_CALLOUT_printf("callout_run(%p) tnow=%u ticks=%u evq=%p\n", c, (uint)tnow, (uint)c->ticks, c->evq);
            c->active = false;
            if (c->evq) {
                ble_npl_eventq_put(c->evq, &c->ev);
            } else {
                c->ev.fn(&c->ev);
            }
            DEBUG_CALLOUT_printf("callout_run(%p) done\n", c);
        }
    }
}