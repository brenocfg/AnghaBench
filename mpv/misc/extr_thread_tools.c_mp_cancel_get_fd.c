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
struct mp_cancel {scalar_t__* wakeup_pipe; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_make_wakeup_pipe (scalar_t__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retrigger_locked (struct mp_cancel*) ; 

int mp_cancel_get_fd(struct mp_cancel *c)
{
    pthread_mutex_lock(&c->lock);
    if (c->wakeup_pipe[0] < 0) {
        mp_make_wakeup_pipe(c->wakeup_pipe);
        retrigger_locked(c);
    }
    pthread_mutex_unlock(&c->lock);


    return c->wakeup_pipe[0];
}