#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cv; } ;
typedef  TYPE_1__ nn_condvar_t ;

/* Variables and functions */
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nn_condvar_init (nn_condvar_t *cond)
{
    int rc;

    /* This should really never fail, but the system may do so for
       ENOMEM or EAGAIN due to resource exhaustion, or EBUSY if reusing
       a condition variable with no intervening destroy call. */
    rc = pthread_cond_init (&cond->cv, NULL);
    return (-rc);
}