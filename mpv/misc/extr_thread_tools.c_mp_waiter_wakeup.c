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
struct mp_waiter {int done; uintptr_t value; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_waiter_wakeup(struct mp_waiter *waiter, uintptr_t value)
{
    pthread_mutex_lock(&waiter->lock);
    assert(!waiter->done);
    waiter->done = true;
    waiter->value = value;
    pthread_cond_signal(&waiter->wakeup);
    pthread_mutex_unlock(&waiter->lock);
}