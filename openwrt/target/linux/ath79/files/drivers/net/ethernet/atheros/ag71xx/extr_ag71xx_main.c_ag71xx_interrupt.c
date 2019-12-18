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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct ag71xx {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AG71XX_INT_ERR ; 
 int AG71XX_INT_POLL ; 
 int AG71XX_INT_RX_BE ; 
 int AG71XX_INT_TX_BE ; 
 int /*<<< orphan*/  AG71XX_REG_INT_STATUS ; 
 int /*<<< orphan*/  AG71XX_REG_RX_STATUS ; 
 int /*<<< orphan*/  AG71XX_REG_TX_STATUS ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RX_STATUS_BE ; 
 int /*<<< orphan*/  TX_STATUS_BE ; 
 int /*<<< orphan*/  ag71xx_debugfs_update_int_stats (struct ag71xx*,int) ; 
 int /*<<< orphan*/  ag71xx_dump_intr (struct ag71xx*,char*,int) ; 
 int /*<<< orphan*/  ag71xx_int_disable (struct ag71xx*,int) ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ag71xx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct ag71xx *ag = netdev_priv(dev);
	u32 status;

	status = ag71xx_rr(ag, AG71XX_REG_INT_STATUS);
	ag71xx_dump_intr(ag, "raw", status);

	if (unlikely(!status))
		return IRQ_NONE;

	if (unlikely(status & AG71XX_INT_ERR)) {
		if (status & AG71XX_INT_TX_BE) {
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE);
			dev_err(&dev->dev, "TX BUS error\n");
		}
		if (status & AG71XX_INT_RX_BE) {
			ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE);
			dev_err(&dev->dev, "RX BUS error\n");
		}
	}

	if (likely(status & AG71XX_INT_POLL)) {
		ag71xx_int_disable(ag, AG71XX_INT_POLL);
		DBG("%s: enable polling mode\n", dev->name);
		napi_schedule(&ag->napi);
	}

	ag71xx_debugfs_update_int_stats(ag, status);

	return IRQ_HANDLED;
}