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
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int pthread_cond_destroy (int /*<<< orphan*/ *) ; 

void nn_condvar_term (nn_condvar_t *cond)
{
    int rc;

    /* This should never fail, the system is allowed to return EBUSY if
       there are outstanding waiters (a serious bug!), or EINVAL if the
       cv is somehow invalid or illegal.  Either of these cases would
       represent a serious programming defect in our caller. */
    rc = pthread_cond_destroy (&cond->cv);
    errnum_assert (rc == 0, rc);
}