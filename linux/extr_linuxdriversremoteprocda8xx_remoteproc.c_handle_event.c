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
struct rproc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  rproc_vq_interrupt (struct rproc*,int) ; 

__attribute__((used)) static irqreturn_t handle_event(int irq, void *p)
{
	struct rproc *rproc = (struct rproc *)p;

	/* Process incoming buffers on all our vrings */
	rproc_vq_interrupt(rproc, 0);
	rproc_vq_interrupt(rproc, 1);

	return IRQ_HANDLED;
}