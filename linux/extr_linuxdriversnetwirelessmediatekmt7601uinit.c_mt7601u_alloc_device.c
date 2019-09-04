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
struct mt7601u_dev {int /*<<< orphan*/  stat_wq; int /*<<< orphan*/  tx_skb_done; int /*<<< orphan*/  avg_ampdu_len; int /*<<< orphan*/  con_mon_lock; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_atomic_mutex; int /*<<< orphan*/  reg_atomic_mutex; int /*<<< orphan*/  vendor_req_mutex; struct ieee80211_hw* hw; struct device* dev; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mt7601u_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mt7601u_dev *mt7601u_alloc_device(struct device *pdev)
{
	struct ieee80211_hw *hw;
	struct mt7601u_dev *dev;

	hw = ieee80211_alloc_hw(sizeof(*dev), &mt7601u_ops);
	if (!hw)
		return NULL;

	dev = hw->priv;
	dev->dev = pdev;
	dev->hw = hw;
	mutex_init(&dev->vendor_req_mutex);
	mutex_init(&dev->reg_atomic_mutex);
	mutex_init(&dev->hw_atomic_mutex);
	mutex_init(&dev->mutex);
	spin_lock_init(&dev->tx_lock);
	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->mac_lock);
	spin_lock_init(&dev->con_mon_lock);
	atomic_set(&dev->avg_ampdu_len, 1);
	skb_queue_head_init(&dev->tx_skb_done);

	dev->stat_wq = alloc_workqueue("mt7601u", WQ_UNBOUND, 0);
	if (!dev->stat_wq) {
		ieee80211_free_hw(hw);
		return NULL;
	}

	return dev;
}