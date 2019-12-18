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
struct TYPE_4__ {void* arg; struct TYPE_4__* next; int /*<<< orphan*/  (* handfn ) (void*) ;} ;
typedef  TYPE_1__ THREAD_EVENT_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void init_thread_stop(void *arg, THREAD_EVENT_HANDLER **hands)
{
    THREAD_EVENT_HANDLER *curr, *prev = NULL;

    /* Can't do much about this */
    if (hands == NULL)
        return;

    curr = *hands;
    while (curr != NULL) {
        if (arg != NULL && curr->arg != arg) {
            curr = curr->next;
            continue;
        }
        curr->handfn(curr->arg);
        prev = curr;
        curr = curr->next;
        if (prev == *hands)
            *hands = curr;
        OPENSSL_free(prev);
    }
}