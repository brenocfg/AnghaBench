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
struct nn_sock {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_ctx_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_leave (int /*<<< orphan*/ *) ; 
 int nn_sock_getopt_inner (struct nn_sock*,int,int,void*,size_t*) ; 

int nn_sock_getopt (struct nn_sock *self, int level, int option,
    void *optval, size_t *optvallen)
{
    int rc;

    nn_ctx_enter (&self->ctx);
    rc = nn_sock_getopt_inner (self, level, option, optval, optvallen);
    nn_ctx_leave (&self->ctx);

    return rc;
}