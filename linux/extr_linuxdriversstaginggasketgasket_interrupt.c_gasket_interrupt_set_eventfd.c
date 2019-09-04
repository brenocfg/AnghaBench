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
struct gasket_interrupt_data {int num_interrupts; struct eventfd_ctx** eventfd_ctxs; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 

int gasket_interrupt_set_eventfd(struct gasket_interrupt_data *interrupt_data,
				 int interrupt, int event_fd)
{
	struct eventfd_ctx *ctx = eventfd_ctx_fdget(event_fd);

	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	if (interrupt < 0 || interrupt >= interrupt_data->num_interrupts)
		return -EINVAL;

	interrupt_data->eventfd_ctxs[interrupt] = ctx;
	return 0;
}