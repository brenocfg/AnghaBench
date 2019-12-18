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
struct nn_ep {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int nn_sock_getopt_inner (int /*<<< orphan*/ ,int,int,void*,size_t*) ; 

void nn_ep_getopt (struct nn_ep *self, int level, int option,
    void *optval, size_t *optvallen)
{
    int rc;

    rc = nn_sock_getopt_inner (self->sock, level, option, optval, optvallen);
    errnum_assert (rc == 0, -rc);
}