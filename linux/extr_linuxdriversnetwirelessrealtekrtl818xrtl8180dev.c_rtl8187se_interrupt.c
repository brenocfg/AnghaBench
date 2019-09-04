#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtl8180_priv {int /*<<< orphan*/  lock; TYPE_1__* map; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8180_priv* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  INT_TIMEOUT; int /*<<< orphan*/  INT_STATUS_SE; } ;

/* Variables and functions */
 int IMR_RER ; 
 int IMR_ROK ; 
 int IMR_RQOSOK ; 
 int IMR_TBDER ; 
 int IMR_TBDOK ; 
 int IMR_TBEDER ; 
 int IMR_TBEDOK ; 
 int IMR_TBKDER ; 
 int IMR_TBKDOK ; 
 int IMR_TIMEOUT1 ; 
 int IMR_TVIDER ; 
 int IMR_TVIDOK ; 
 int IMR_TVODER ; 
 int IMR_TVODOK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTL818X_INT_SE_RX_DU ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  rtl8180_handle_rx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_handle_tx (struct ieee80211_hw*,int) ; 
 int rtl818x_ioread32 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t rtl8187se_interrupt(int irq, void *dev_id)
{
	struct ieee80211_hw *dev = dev_id;
	struct rtl8180_priv *priv = dev->priv;
	u32 reg;
	unsigned long flags;
	static int desc_err;

	spin_lock_irqsave(&priv->lock, flags);
	/* Note: 32-bit interrupt status */
	reg = rtl818x_ioread32(priv, &priv->map->INT_STATUS_SE);
	if (unlikely(reg == 0xFFFFFFFF)) {
		spin_unlock_irqrestore(&priv->lock, flags);
		return IRQ_HANDLED;
	}

	rtl818x_iowrite32(priv, &priv->map->INT_STATUS_SE, reg);

	if (reg & IMR_TIMEOUT1)
		rtl818x_iowrite32(priv, &priv->map->INT_TIMEOUT, 0);

	if (reg & (IMR_TBDOK | IMR_TBDER))
		rtl8180_handle_tx(dev, 4);

	if (reg & (IMR_TVODOK | IMR_TVODER))
		rtl8180_handle_tx(dev, 0);

	if (reg & (IMR_TVIDOK | IMR_TVIDER))
		rtl8180_handle_tx(dev, 1);

	if (reg & (IMR_TBEDOK | IMR_TBEDER))
		rtl8180_handle_tx(dev, 2);

	if (reg & (IMR_TBKDOK | IMR_TBKDER))
		rtl8180_handle_tx(dev, 3);

	if (reg & (IMR_ROK | IMR_RER | RTL818X_INT_SE_RX_DU | IMR_RQOSOK))
		rtl8180_handle_rx(dev);
	/* The interface sometimes generates several RX DMA descriptor errors
	 * at startup. Do not report these.
	 */
	if ((reg & RTL818X_INT_SE_RX_DU) && desc_err++ > 2)
		if (net_ratelimit())
			wiphy_err(dev->wiphy, "No RX DMA Descriptor avail\n");

	spin_unlock_irqrestore(&priv->lock, flags);
	return IRQ_HANDLED;
}