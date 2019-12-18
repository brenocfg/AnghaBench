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
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

void nn_condvar_signal (nn_condvar_t *cond)
{
    /* The only legal failure mode here is EINVAL if we passed a bad
       condition variable.  We don't check that. */
    (void) pthread_cond_signal (&cond->cv);
}