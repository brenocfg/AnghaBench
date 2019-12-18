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
struct nn_sock {int state; int /*<<< orphan*/  holds; } ;

/* Variables and functions */
 int EBADF ; 
#define  NN_SOCK_STATE_ACTIVE 132 
#define  NN_SOCK_STATE_FINI 131 
#define  NN_SOCK_STATE_INIT 130 
#define  NN_SOCK_STATE_STOPPING 129 
#define  NN_SOCK_STATE_STOPPING_EPS 128 

int nn_sock_hold (struct nn_sock *self)
{
    switch (self->state) {
    case NN_SOCK_STATE_ACTIVE:
    case NN_SOCK_STATE_INIT:
        self->holds++;
        return 0;
    case NN_SOCK_STATE_STOPPING:
    case NN_SOCK_STATE_STOPPING_EPS:
    case NN_SOCK_STATE_FINI:
    default:
        return -EBADF;
    }
}