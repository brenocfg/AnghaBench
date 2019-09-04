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
struct vscsibk_info {scalar_t__ ring_error; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ scsiback_do_cmd_fn (struct vscsibk_info*) ; 

__attribute__((used)) static irqreturn_t scsiback_irq_fn(int irq, void *dev_id)
{
	struct vscsibk_info *info = dev_id;

	if (info->ring_error)
		return IRQ_HANDLED;

	while (scsiback_do_cmd_fn(info))
		cond_resched();

	return IRQ_HANDLED;
}