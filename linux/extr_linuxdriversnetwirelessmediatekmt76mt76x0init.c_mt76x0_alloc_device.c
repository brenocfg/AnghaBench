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
struct TYPE_2__ {int /*<<< orphan*/  lock; struct ieee80211_hw* hw; struct device* dev; } ;
struct mt76x0_dev {int /*<<< orphan*/  stat_wq; int /*<<< orphan*/  tx_skb_done; int /*<<< orphan*/  avg_ampdu_len; int /*<<< orphan*/  con_mon_lock; int /*<<< orphan*/  mac_lock; TYPE_1__ mt76; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_atomic_mutex; int /*<<< orphan*/  reg_atomic_mutex; int /*<<< orphan*/  usb_ctrl_mtx; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mt76x0_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mt76x0_dev *mt76x0_alloc_device(struct device *pdev)
{
	struct ieee80211_hw *hw;
	struct mt76x0_dev *dev;

	hw = ieee80211_alloc_hw(sizeof(*dev), &mt76x0_ops);
	if (!hw)
		return NULL;

	dev = hw->priv;
	dev->mt76.dev = pdev;
	dev->mt76.hw = hw;
	mutex_init(&dev->usb_ctrl_mtx);
	mutex_init(&dev->reg_atomic_mutex);
	mutex_init(&dev->hw_atomic_mutex);
	mutex_init(&dev->mutex);
	spin_lock_init(&dev->tx_lock);
	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->mt76.lock);
	spin_lock_init(&dev->mac_lock);
	spin_lock_init(&dev->con_mon_lock);
	atomic_set(&dev->avg_ampdu_len, 1);
	skb_queue_head_init(&dev->tx_skb_done);

	dev->stat_wq = alloc_workqueue("mt76x0", WQ_UNBOUND, 0);
	if (!dev->stat_wq) {
		ieee80211_free_hw(hw);
		return NULL;
	}

	return dev;
}