#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ta_header {scalar_t__ canary; TYPE_1__* leak_prev; TYPE_2__* leak_next; } ;
struct TYPE_4__ {TYPE_1__* leak_prev; } ;
struct TYPE_3__ {TYPE_2__* leak_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ta_dbg_check_header (struct ta_header*) ; 
 int /*<<< orphan*/  ta_dbg_mutex ; 

__attribute__((used)) static void ta_dbg_remove(struct ta_header *h)
{
    ta_dbg_check_header(h);
    if (h->leak_next) { // assume checking for !=NULL invariant ok without lock
        pthread_mutex_lock(&ta_dbg_mutex);
        h->leak_next->leak_prev = h->leak_prev;
        h->leak_prev->leak_next = h->leak_next;
        pthread_mutex_unlock(&ta_dbg_mutex);
        h->leak_next = h->leak_prev = NULL;
    }
    h->canary = 0;
}