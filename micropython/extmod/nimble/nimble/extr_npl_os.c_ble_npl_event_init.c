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
struct ble_npl_event {int /*<<< orphan*/ * next; void* arg; int /*<<< orphan*/ * fn; } ;
typedef  int /*<<< orphan*/  ble_npl_event_fn ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT_printf (char*,struct ble_npl_event*,int /*<<< orphan*/ *,void*) ; 

void ble_npl_event_init(struct ble_npl_event *ev, ble_npl_event_fn *fn, void *arg) {
    DEBUG_EVENT_printf("ble_npl_event_init(%p, %p, %p)\n", ev, fn, arg);
    ev->fn = fn;
    ev->arg = arg;
    ev->next = NULL;
}