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
struct nn_sem {int signaled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void nn_sem_post (struct nn_sem *self)
{
    int rc;

    rc = pthread_mutex_lock (&self->mutex);
    errnum_assert (rc == 0, rc);
    nn_assert (self->signaled == 0);
    self->signaled = 1;
    rc = pthread_cond_signal (&self->cond);
    errnum_assert (rc == 0, rc);
    rc = pthread_mutex_unlock (&self->mutex);
    errnum_assert (rc == 0, rc);
}