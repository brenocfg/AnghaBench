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
struct ble_npl_eventq {struct ble_npl_event* head; } ;
struct ble_npl_event {struct ble_npl_event* prev; struct ble_npl_event* next; int /*<<< orphan*/  arg; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT_printf (char*,...) ; 

void ble_npl_eventq_put(struct ble_npl_eventq *evq, struct ble_npl_event *ev) {
    DEBUG_EVENT_printf("ble_npl_eventq_put(%p, %p (%p, %p))\n", evq, ev, ev->fn, ev->arg);
    ev->next = NULL;
    if (evq->head == NULL) {
        evq->head = ev;
        ev->prev = NULL;
    } else {
        struct ble_npl_event *ev2 = evq->head;
        while (true) {
            if (ev2 == ev) {
                DEBUG_EVENT_printf("  --> already in queue\n");
                return;
            }
            if (ev2->next == NULL) {
                break;
            }
            DEBUG_EVENT_printf("  --> %p\n", ev2->next);
            ev2 = ev2->next;
        }
        ev2->next = ev;
        ev->prev = ev2;
    }
}