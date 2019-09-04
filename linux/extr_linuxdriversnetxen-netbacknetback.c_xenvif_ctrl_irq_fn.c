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
struct xenvif {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  xenvif_ctrl_action (struct xenvif*) ; 
 scalar_t__ xenvif_ctrl_work_todo (struct xenvif*) ; 

irqreturn_t xenvif_ctrl_irq_fn(int irq, void *data)
{
	struct xenvif *vif = data;

	while (xenvif_ctrl_work_todo(vif))
		xenvif_ctrl_action(vif);

	return IRQ_HANDLED;
}