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
struct nn_sem {int /*<<< orphan*/  mutex; scalar_t__ signaled; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 scalar_t__ nn_fast (scalar_t__) ; 
 scalar_t__ nn_slow (int) ; 
 int pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int nn_sem_wait (struct nn_sem *self)
{
    int rc;

    /*  With OSX, semaphores are global named objects. They are not useful for
        our use case. To get a similar object we exploit the implementation
        detail of pthread_cond_wait() in Darwin kernel: It exits if signal is
        caught. Note that this behaviour is not mandated by POSIX
        and may break with future versions of Darwin. */
    rc = pthread_mutex_lock (&self->mutex);
    errnum_assert (rc == 0, rc);
    if (nn_fast (self->signaled)) {
        rc = pthread_mutex_unlock (&self->mutex);
        errnum_assert (rc == 0, rc);
        return 0;
    }
    rc = pthread_cond_wait (&self->cond, &self->mutex);
    errnum_assert (rc == 0, rc);
    if (nn_slow (!self->signaled)) {
        rc = pthread_mutex_unlock (&self->mutex);
        errnum_assert (rc == 0, rc);
        return -EINTR;
    }
    self->signaled = 0;
    rc = pthread_mutex_unlock (&self->mutex);
    errnum_assert (rc == 0, rc);

    return 0;
}