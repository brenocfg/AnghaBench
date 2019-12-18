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
 int nn_sock_ispeer (int /*<<< orphan*/ ,int) ; 

int nn_ep_ispeer (struct nn_ep *self, int socktype)
{
    return nn_sock_ispeer (self->sock, socktype);
}