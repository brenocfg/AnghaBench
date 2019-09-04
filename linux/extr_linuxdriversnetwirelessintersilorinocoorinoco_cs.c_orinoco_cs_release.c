#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {struct orinoco_private* priv; } ;
struct TYPE_4__ {scalar_t__ iobase; TYPE_1__* ops; } ;
struct orinoco_private {TYPE_2__ hw; int /*<<< orphan*/  lock; int /*<<< orphan*/  hw_unavailable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unlock_irqrestore ) (int /*<<< orphan*/ *,unsigned long*) ;int /*<<< orphan*/  (* lock_irqsave ) (int /*<<< orphan*/ *,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ioport_unmap (scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static void
orinoco_cs_release(struct pcmcia_device *link)
{
	struct orinoco_private *priv = link->priv;
	unsigned long flags;

	/* We're committed to taking the device away now, so mark the
	 * hardware as unavailable */
	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	priv->hw_unavailable++;
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);

	pcmcia_disable_device(link);
	if (priv->hw.iobase)
		ioport_unmap(priv->hw.iobase);
}