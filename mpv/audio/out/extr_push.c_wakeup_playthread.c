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
struct ao_push_state {int need_wakeup; int /*<<< orphan*/  wakeup; } ;
struct ao {TYPE_1__* driver; struct ao_push_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wakeup ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static void wakeup_playthread(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;
    if (ao->driver->wakeup)
        ao->driver->wakeup(ao);
    p->need_wakeup = true;
    pthread_cond_signal(&p->wakeup);
}