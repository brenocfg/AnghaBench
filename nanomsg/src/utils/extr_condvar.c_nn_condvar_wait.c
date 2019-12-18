#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ nn_mutex_t ;
struct TYPE_6__ {int /*<<< orphan*/  cv; } ;
typedef  TYPE_2__ nn_condvar_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nn_condvar_wait (nn_condvar_t *cond, nn_mutex_t *lock, int timeout)
{
    int rc;
    struct timeval tv;
    struct timespec ts;

    if (timeout < 0) {
        /*  This is an infinite sleep.  We don't care about return values,
            as any error we can treat as just a premature wakeup. */
        (void) pthread_cond_wait (&cond->cv, &lock->mutex);
        return (0);
    }

    rc = gettimeofday(&tv, NULL);
    errnum_assert (rc == 0, rc);

    /* There are extra operations performed here, but they are done to avoid
       wrap of the tv_usec and ts_nsec members on 32-bit systems. */
    tv.tv_sec += timeout / 1000;
    tv.tv_usec += (timeout % 1000) * 1000;

    ts.tv_sec = tv.tv_sec + (tv.tv_usec / 1000000);
    ts.tv_nsec = (tv.tv_usec % 1000000) * 1000;

    rc = pthread_cond_timedwait (&cond->cv, &lock->mutex, &ts);
    if (rc == ETIMEDOUT)
        return (-ETIMEDOUT);
    /* Treat all other cases (including errors) as normal wakeup. */
    return (0);
}