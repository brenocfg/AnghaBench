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
struct ao_push_state {int need_wakeup; int initial_unblocked; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; } ;
struct ao {struct ao_push_state* api_priv; int /*<<< orphan*/ * api; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_api_push ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_playthread (struct ao*) ; 

void ao_unblock(struct ao *ao)
{
    if (ao->api == &ao_api_push) {
        struct ao_push_state *p = ao->api_priv;
        pthread_mutex_lock(&p->lock);
        p->need_wakeup = true;
        p->initial_unblocked = true;
        wakeup_playthread(ao);
        pthread_cond_signal(&p->wakeup);
        pthread_mutex_unlock(&p->lock);
    }
}