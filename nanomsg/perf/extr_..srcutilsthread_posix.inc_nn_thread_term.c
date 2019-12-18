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
struct nn_thread {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_thread_term (struct nn_thread *self)
{
    int rc;

    rc = pthread_join (self->handle, NULL);
    errnum_assert (rc == 0, rc);
}