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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {scalar_t__ oldduplex; int speed; int oldlink; int /*<<< orphan*/  eee_enabled; int /*<<< orphan*/  lock; scalar_t__ ioaddr; int /*<<< orphan*/  dev; TYPE_2__* hw; } ;
struct phy_device {scalar_t__ duplex; int speed; int /*<<< orphan*/  irq; scalar_t__ is_pseudo_fixed_link; scalar_t__ pause; scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed10; int /*<<< orphan*/  speed100; int /*<<< orphan*/  speed1000; int /*<<< orphan*/  speed_mask; int /*<<< orphan*/  duplex; } ;
struct TYPE_4__ {TYPE_1__ link; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_UNKNOWN ; 
 scalar_t__ MAC_CTRL_REG ; 
 int /*<<< orphan*/  PHY_IGNORE_INTERRUPT ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 void* SPEED_UNKNOWN ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct stmmac_priv*) ; 
 int /*<<< orphan*/  netif_warn (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stmmac_eee_init (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_hw_fix_mac_speed (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_flow_ctrl (struct stmmac_priv*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stmmac_adjust_link(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	bool new_state = false;

	if (!phydev)
		return;

	mutex_lock(&priv->lock);

	if (phydev->link) {
		u32 ctrl = readl(priv->ioaddr + MAC_CTRL_REG);

		/* Now we make sure that we can be in full duplex mode.
		 * If not, we operate in half-duplex mode. */
		if (phydev->duplex != priv->oldduplex) {
			new_state = true;
			if (!phydev->duplex)
				ctrl &= ~priv->hw->link.duplex;
			else
				ctrl |= priv->hw->link.duplex;
			priv->oldduplex = phydev->duplex;
		}
		/* Flow Control operation */
		if (phydev->pause)
			stmmac_mac_flow_ctrl(priv, phydev->duplex);

		if (phydev->speed != priv->speed) {
			new_state = true;
			ctrl &= ~priv->hw->link.speed_mask;
			switch (phydev->speed) {
			case SPEED_1000:
				ctrl |= priv->hw->link.speed1000;
				break;
			case SPEED_100:
				ctrl |= priv->hw->link.speed100;
				break;
			case SPEED_10:
				ctrl |= priv->hw->link.speed10;
				break;
			default:
				netif_warn(priv, link, priv->dev,
					   "broken speed: %d\n", phydev->speed);
				phydev->speed = SPEED_UNKNOWN;
				break;
			}
			if (phydev->speed != SPEED_UNKNOWN)
				stmmac_hw_fix_mac_speed(priv);
			priv->speed = phydev->speed;
		}

		writel(ctrl, priv->ioaddr + MAC_CTRL_REG);

		if (!priv->oldlink) {
			new_state = true;
			priv->oldlink = true;
		}
	} else if (priv->oldlink) {
		new_state = true;
		priv->oldlink = false;
		priv->speed = SPEED_UNKNOWN;
		priv->oldduplex = DUPLEX_UNKNOWN;
	}

	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);

	mutex_unlock(&priv->lock);

	if (phydev->is_pseudo_fixed_link)
		/* Stop PHY layer to call the hook to adjust the link in case
		 * of a switch is attached to the stmmac driver.
		 */
		phydev->irq = PHY_IGNORE_INTERRUPT;
	else
		/* At this stage, init the EEE if supported.
		 * Never called in case of fixed_link.
		 */
		priv->eee_enabled = stmmac_eee_init(priv);
}