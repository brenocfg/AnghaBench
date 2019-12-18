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
struct ble_npl_eventq {struct ble_npl_eventq* nextq; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT_printf (char*,struct ble_npl_eventq*) ; 
 struct ble_npl_eventq* global_eventq ; 

void ble_npl_eventq_init(struct ble_npl_eventq *evq) {
    DEBUG_EVENT_printf("ble_npl_eventq_init(%p)\n", evq);
    evq->head = NULL;
    struct ble_npl_eventq **evq2;
    for (evq2 = &global_eventq; *evq2 != NULL; evq2 = &(*evq2)->nextq) {
    }
    *evq2 = evq;
    evq->nextq = NULL;
}