#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43_phy {TYPE_2__* ops; int /*<<< orphan*/  next_txpwr_check_time; } ;
struct b43_wldev {TYPE_3__* wl; TYPE_1__* dev; struct b43_phy phy; } ;
typedef  enum b43_txpwr_result { ____Placeholder_b43_txpwr_result } b43_txpwr_result ;
struct TYPE_6__ {int /*<<< orphan*/  txpower_adjust_work; int /*<<< orphan*/  hw; } ;
struct TYPE_5__ {int (* recalc_txpower ) (struct b43_wldev*,int) ;int /*<<< orphan*/ * adjust_txpower; } ;
struct TYPE_4__ {scalar_t__ board_vendor; scalar_t__ board_type; } ;

/* Variables and functions */
 unsigned int B43_TXPWR_IGNORE_TIME ; 
 unsigned int B43_TXPWR_IGNORE_TSSI ; 
 int B43_TXPWR_RES_DONE ; 
 int B43_TXPWR_RES_NEED_ADJUST ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int HZ ; 
 scalar_t__ SSB_BOARDVENDOR_BCM ; 
 scalar_t__ SSB_BOARD_BU4306 ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  round_jiffies (unsigned long) ; 
 int stub1 (struct b43_wldev*,int) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 

void b43_phy_txpower_check(struct b43_wldev *dev, unsigned int flags)
{
	struct b43_phy *phy = &dev->phy;
	unsigned long now = jiffies;
	enum b43_txpwr_result result;

	if (!(flags & B43_TXPWR_IGNORE_TIME)) {
		/* Check if it's time for a TXpower check. */
		if (time_before(now, phy->next_txpwr_check_time))
			return; /* Not yet */
	}
	/* The next check will be needed in two seconds, or later. */
	phy->next_txpwr_check_time = round_jiffies(now + (HZ * 2));

	if ((dev->dev->board_vendor == SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type == SSB_BOARD_BU4306))
		return; /* No software txpower adjustment needed */

	result = phy->ops->recalc_txpower(dev, !!(flags & B43_TXPWR_IGNORE_TSSI));
	if (result == B43_TXPWR_RES_DONE)
		return; /* We are done. */
	B43_WARN_ON(result != B43_TXPWR_RES_NEED_ADJUST);
	B43_WARN_ON(phy->ops->adjust_txpower == NULL);

	/* We must adjust the transmission power in hardware.
	 * Schedule b43_phy_txpower_adjust_work(). */
	ieee80211_queue_work(dev->wl->hw, &dev->wl->txpower_adjust_work);
}