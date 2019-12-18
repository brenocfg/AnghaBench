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
struct nn_thread {int /*<<< orphan*/  handle; void* arg; int /*<<< orphan*/ * routine; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  nn_thread_routine ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_thread_main_routine ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sigfillset (int /*<<< orphan*/ *) ; 

void nn_thread_init (struct nn_thread *self,
    nn_thread_routine *routine, void *arg)
{
    int rc;
    sigset_t new_sigmask;
    sigset_t old_sigmask;
 
    /*  No signals should be processed by this thread. The library doesn't
        use signals and thus all the signals should be delivered to application
        threads, not to worker threads. */
    rc = sigfillset (&new_sigmask);
    errno_assert (rc == 0);
    rc = pthread_sigmask (SIG_BLOCK, &new_sigmask, &old_sigmask);
    errnum_assert (rc == 0, rc);

    self->routine = routine;
    self->arg = arg;
    rc = pthread_create (&self->handle, NULL, nn_thread_main_routine,
        (void*) self);
    errnum_assert (rc == 0, rc);

    /*  Restore signal set to what it was before. */
    rc = pthread_sigmask (SIG_SETMASK, &old_sigmask, NULL);
    errnum_assert (rc == 0, rc);
}