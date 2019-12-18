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
struct ble_npl_eventq {int dummy; } ;
struct ble_npl_callout {int active; struct ble_npl_callout* nextc; int /*<<< orphan*/  ev; struct ble_npl_eventq* evq; scalar_t__ ticks; } ;
typedef  int /*<<< orphan*/  ble_npl_event_fn ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CALLOUT_printf (char*,struct ble_npl_callout*,struct ble_npl_eventq*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ble_npl_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 struct ble_npl_callout* global_callout ; 

void ble_npl_callout_init(struct ble_npl_callout *c, struct ble_npl_eventq *evq, ble_npl_event_fn *ev_cb, void *ev_arg) {
    DEBUG_CALLOUT_printf("ble_npl_callout_init(%p, %p, %p, %p)\n", c, evq, ev_cb, ev_arg);
    c->active = false;
    c->ticks = 0;
    c->evq = evq;
    ble_npl_event_init(&c->ev, ev_cb, ev_arg);

    struct ble_npl_callout **c2;
    for (c2 = &global_callout; *c2 != NULL; c2 = &(*c2)->nextc) {
        if (c == *c2) {
            // callout already in linked list so don't link it in again
            return;
        }
    }
    *c2 = c;
    c->nextc = NULL;
}