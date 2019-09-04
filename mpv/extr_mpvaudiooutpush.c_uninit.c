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
struct ao_push_state {int terminate; int /*<<< orphan*/  thread; int /*<<< orphan*/  lock; } ;
struct ao {struct ao_push_state* api_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_no_thread (struct ao*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_playthread (struct ao*) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;

    pthread_mutex_lock(&p->lock);
    p->terminate = true;
    wakeup_playthread(ao);
    pthread_mutex_unlock(&p->lock);

    pthread_join(p->thread, NULL);

    destroy_no_thread(ao);
}