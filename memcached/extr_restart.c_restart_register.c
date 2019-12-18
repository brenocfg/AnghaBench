#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * restart_save_cb ;
struct TYPE_4__ {int /*<<< orphan*/  scb; int /*<<< orphan*/  ccb; void* data; int /*<<< orphan*/  tag; struct TYPE_4__* next; } ;
typedef  TYPE_1__ restart_data_cb ;
typedef  int /*<<< orphan*/ * restart_check_cb ;

/* Variables and functions */
 int /*<<< orphan*/  RESTART_TAG_MAXLEN ; 
 TYPE_1__* calloc (int,int) ; 
 TYPE_1__* cb_stack ; 
 int /*<<< orphan*/  safe_strcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void restart_register(const char *tag, restart_check_cb ccb, restart_save_cb scb, void *data) {
    restart_data_cb *cb = calloc(1, sizeof(restart_data_cb));

    // Handle first time call initialization inline so we don't need separate
    // API call.
    if (cb_stack == NULL) {
        cb_stack = cb;
    } else {
        // Ensure we fire the callbacks in registration order.
        // Someday I'll get a queue.h overhaul.
        restart_data_cb *finder = cb_stack;
        while (finder->next != NULL) {
            finder = finder->next;
        }
        finder->next = cb;
    }

    safe_strcpy(cb->tag, tag, RESTART_TAG_MAXLEN);
    cb->data = data;
    cb->ccb = *ccb;
    cb->scb = *scb;
}