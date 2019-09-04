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
struct timeout {void (* func ) (void*) ;void* what; struct timeout* next; } ;

/* Variables and functions */
 struct timeout* free_timeouts ; 
 struct timeout* timeouts ; 

void
cancel_timeout(void (*where)(void *), void *what)
{
    struct timeout *t, *q;

    /* Look for this timeout on the list, and unlink it if we find it. */
    t = NULL;
    for (q = timeouts; q; q = q->next) {
        if (q->func == where && q->what == what) {
            if (t)
                t->next = q->next;
            else
                timeouts = q->next;
            break;
        }
        t = q;
    }

    /* If we found the timeout, put it on the free list. */
    if (q) {
        q->next = free_timeouts;
        free_timeouts = q;
    }
}