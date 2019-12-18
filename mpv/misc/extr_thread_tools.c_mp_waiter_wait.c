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
struct mp_waiter {uintptr_t value; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mp_waiter*,int,int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

uintptr_t mp_waiter_wait(struct mp_waiter *waiter)
{
    pthread_mutex_lock(&waiter->lock);
    while (!waiter->done)
        pthread_cond_wait(&waiter->wakeup, &waiter->lock);
    pthread_mutex_unlock(&waiter->lock);

    uintptr_t ret = waiter->value;

    // We document that after mp_waiter_wait() the waiter object becomes
    // invalid. (It strictly returns only after mp_waiter_wakeup() has returned,
    // and the object is "single-shot".) So destroy it here.

    // Normally, we expect that the system uses futexes, in which case the
    // following functions will do nearly nothing. This is true for Windows
    // and Linux. But some lesser OSes still might allocate kernel objects
    // when initializing mutexes, so destroy them here.
    pthread_mutex_destroy(&waiter->lock);
    pthread_cond_destroy(&waiter->wakeup);

    memset(waiter, 0xCA, sizeof(*waiter)); // for debugging

    return ret;
}