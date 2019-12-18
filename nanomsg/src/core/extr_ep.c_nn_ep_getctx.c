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
struct nn_ctx {int dummy; } ;

/* Variables and functions */
 struct nn_ctx* nn_sock_getctx (int /*<<< orphan*/ ) ; 

struct nn_ctx *nn_ep_getctx (struct nn_ep *self)
{
    return nn_sock_getctx (self->sock);
}