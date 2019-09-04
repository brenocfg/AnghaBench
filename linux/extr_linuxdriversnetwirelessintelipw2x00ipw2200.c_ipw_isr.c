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
typedef  int u32 ;
struct ipw_priv {int status; int isr_inta; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IPW_INTA_MASK_ALL ; 
 int /*<<< orphan*/  IPW_INTA_MASK_R ; 
 int /*<<< orphan*/  IPW_INTA_RW ; 
 int /*<<< orphan*/  IPW_WARNING (char*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  __ipw_disable_interrupts (struct ipw_priv*) ; 
 int ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ipw_isr(int irq, void *data)
{
	struct ipw_priv *priv = data;
	u32 inta, inta_mask;

	if (!priv)
		return IRQ_NONE;

	spin_lock(&priv->irq_lock);

	if (!(priv->status & STATUS_INT_ENABLED)) {
		/* IRQ is disabled */
		goto none;
	}

	inta = ipw_read32(priv, IPW_INTA_RW);
	inta_mask = ipw_read32(priv, IPW_INTA_MASK_R);

	if (inta == 0xFFFFFFFF) {
		/* Hardware disappeared */
		IPW_WARNING("IRQ INTA == 0xFFFFFFFF\n");
		goto none;
	}

	if (!(inta & (IPW_INTA_MASK_ALL & inta_mask))) {
		/* Shared interrupt */
		goto none;
	}

	/* tell the device to stop sending interrupts */
	__ipw_disable_interrupts(priv);

	/* ack current interrupts */
	inta &= (IPW_INTA_MASK_ALL & inta_mask);
	ipw_write32(priv, IPW_INTA_RW, inta);

	/* Cache INTA value for our tasklet */
	priv->isr_inta = inta;

	tasklet_schedule(&priv->irq_tasklet);

	spin_unlock(&priv->irq_lock);

	return IRQ_HANDLED;
      none:
	spin_unlock(&priv->irq_lock);
	return IRQ_NONE;
}