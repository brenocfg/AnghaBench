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
struct net_device {int dummy; } ;
struct cpmac_priv {int /*<<< orphan*/  regs; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_MAC_EOI_VECTOR ; 
 int /*<<< orphan*/  CPMAC_MAC_INT_VECTOR ; 
 int /*<<< orphan*/  CPMAC_RX_INT_CLEAR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAC_INT_HOST ; 
 int MAC_INT_RX ; 
 int MAC_INT_STATUS ; 
 int MAC_INT_TX ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpmac_check_status (struct net_device*) ; 
 int /*<<< orphan*/  cpmac_end_xmit (struct net_device*,int) ; 
 int cpmac_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int netif_msg_intr (struct cpmac_priv*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t cpmac_irq(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct cpmac_priv *priv;
	int queue;
	u32 status;

	priv = netdev_priv(dev);

	status = cpmac_read(priv->regs, CPMAC_MAC_INT_VECTOR);

	if (unlikely(netif_msg_intr(priv)))
		netdev_dbg(dev, "interrupt status: 0x%08x\n", status);

	if (status & MAC_INT_TX)
		cpmac_end_xmit(dev, (status & 7));

	if (status & MAC_INT_RX) {
		queue = (status >> 8) & 7;
		if (napi_schedule_prep(&priv->napi)) {
			cpmac_write(priv->regs, CPMAC_RX_INT_CLEAR, 1 << queue);
			__napi_schedule(&priv->napi);
		}
	}

	cpmac_write(priv->regs, CPMAC_MAC_EOI_VECTOR, 0);

	if (unlikely(status & (MAC_INT_HOST | MAC_INT_STATUS)))
		cpmac_check_status(dev);

	return IRQ_HANDLED;
}