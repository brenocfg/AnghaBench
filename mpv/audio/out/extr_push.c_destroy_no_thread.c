#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ao_push_state {int* wakeup_pipe; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; } ;
struct ao {TYPE_1__* driver; struct ao_push_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static void destroy_no_thread(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;

    ao->driver->uninit(ao);

    for (int n = 0; n < 2; n++) {
        int h = p->wakeup_pipe[n];
        if (h >= 0)
            close(h);
    }

    pthread_cond_destroy(&p->wakeup);
    pthread_mutex_destroy(&p->lock);
}