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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ expires; int /*<<< orphan*/ * function; } ;
struct tlan_priv {int timer_type; int /*<<< orphan*/  lock; TYPE_1__ timer; scalar_t__ timer_set_at; struct net_device* dev; } ;
struct timer_list {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_LED_LINK ; 
 int /*<<< orphan*/  TLAN_LED_REG ; 
#define  TLAN_TIMER_ACTIVITY 134 
 scalar_t__ TLAN_TIMER_ACT_DELAY ; 
#define  TLAN_TIMER_FINISH_RESET 133 
#define  TLAN_TIMER_PHY_FINISH_AN 132 
#define  TLAN_TIMER_PHY_PDOWN 131 
#define  TLAN_TIMER_PHY_PUP 130 
#define  TLAN_TIMER_PHY_RESET 129 
#define  TLAN_TIMER_PHY_START_LINK 128 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct tlan_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct tlan_priv* priv ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tlan_dio_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_finish_reset (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_finish_auto_neg (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_power_down (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_power_up (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_reset (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_start_link (struct net_device*) ; 

__attribute__((used)) static void tlan_timer(struct timer_list *t)
{
	struct tlan_priv	*priv = from_timer(priv, t, timer);
	struct net_device	*dev = priv->dev;
	u32		elapsed;
	unsigned long	flags = 0;

	priv->timer.function = NULL;

	switch (priv->timer_type) {
	case TLAN_TIMER_PHY_PDOWN:
		tlan_phy_power_down(dev);
		break;
	case TLAN_TIMER_PHY_PUP:
		tlan_phy_power_up(dev);
		break;
	case TLAN_TIMER_PHY_RESET:
		tlan_phy_reset(dev);
		break;
	case TLAN_TIMER_PHY_START_LINK:
		tlan_phy_start_link(dev);
		break;
	case TLAN_TIMER_PHY_FINISH_AN:
		tlan_phy_finish_auto_neg(dev);
		break;
	case TLAN_TIMER_FINISH_RESET:
		tlan_finish_reset(dev);
		break;
	case TLAN_TIMER_ACTIVITY:
		spin_lock_irqsave(&priv->lock, flags);
		if (priv->timer.function == NULL) {
			elapsed = jiffies - priv->timer_set_at;
			if (elapsed >= TLAN_TIMER_ACT_DELAY) {
				tlan_dio_write8(dev->base_addr,
						TLAN_LED_REG, TLAN_LED_LINK);
			} else  {
				priv->timer.expires = priv->timer_set_at
					+ TLAN_TIMER_ACT_DELAY;
				spin_unlock_irqrestore(&priv->lock, flags);
				add_timer(&priv->timer);
				break;
			}
		}
		spin_unlock_irqrestore(&priv->lock, flags);
		break;
	default:
		break;
	}

}