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
struct nn_sem {scalar_t__ signaled; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_sem_init (struct nn_sem *self)
{
    int rc;

    rc = pthread_mutex_init (&self->mutex, NULL);
    errnum_assert (rc == 0, rc);
    rc = pthread_cond_init (&self->cond, NULL);
    errnum_assert (rc == 0, rc);
    self->signaled = 0;
}