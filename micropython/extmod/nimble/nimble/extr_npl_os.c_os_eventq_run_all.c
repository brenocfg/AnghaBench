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
struct ble_npl_eventq {struct ble_npl_event* head; struct ble_npl_eventq* nextq; } ;
struct ble_npl_event {int /*<<< orphan*/  (* fn ) (struct ble_npl_event*) ;int /*<<< orphan*/ * prev; struct ble_npl_event* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT_printf (char*,struct ble_npl_event*) ; 
 struct ble_npl_eventq* global_eventq ; 
 int /*<<< orphan*/  stub1 (struct ble_npl_event*) ; 

void os_eventq_run_all(void) {
    for (struct ble_npl_eventq *evq = global_eventq; evq != NULL; evq = evq->nextq) {
        while (evq->head != NULL) {
            struct ble_npl_event *ev = evq->head;
            evq->head = ev->next;
            if (ev->next) {
                ev->next->prev = NULL;
                ev->next = NULL;
            }
            ev->prev = NULL;
            DEBUG_EVENT_printf("event_run(%p)\n", ev);
            ev->fn(ev);
            DEBUG_EVENT_printf("event_run(%p) done\n", ev);
        }
    }
}