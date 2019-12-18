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
struct nn_ep_ops {int dummy; } ;
struct nn_ep {void* tran; struct nn_ep_ops ops; } ;

/* Variables and functions */

void nn_ep_tran_setup (struct nn_ep *ep, const struct nn_ep_ops *ops,
    void *tran)
{
    ep->ops = *ops;
    ep->tran = tran;
}