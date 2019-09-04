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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;
struct mt76_wcid {int tx_rate_set; int /*<<< orphan*/  tx_rate_nss; int /*<<< orphan*/  tx_rate; } ;
struct ieee80211_tx_rate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x0_mac_tx_rate_val (struct mt76x0_dev*,struct ieee80211_tx_rate const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mt76x0_mac_wcid_set_rate(struct mt76x0_dev *dev, struct mt76_wcid *wcid,
			    const struct ieee80211_tx_rate *rate)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->mt76.lock, flags);
	wcid->tx_rate = mt76x0_mac_tx_rate_val(dev, rate, &wcid->tx_rate_nss);
	wcid->tx_rate_set = true;
	spin_unlock_irqrestore(&dev->mt76.lock, flags);
}