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
struct sk_buff {int dummy; } ;
struct i2400m {int /*<<< orphan*/  tx_lock; struct sk_buff* wake_tx_skb; int /*<<< orphan*/  wake_tx_ws; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_put (struct i2400m*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i2400m_net_wake_stop(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *wake_tx_skb;
	unsigned long flags;

	d_fnstart(3, dev, "(i2400m %p)\n", i2400m);
	/*
	 * See i2400m_hard_start_xmit(), references are taken there and
	 * here we release them if the packet was still pending.
	 */
	cancel_work_sync(&i2400m->wake_tx_ws);

	spin_lock_irqsave(&i2400m->tx_lock, flags);
	wake_tx_skb = i2400m->wake_tx_skb;
	i2400m->wake_tx_skb = NULL;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);

	if (wake_tx_skb) {
		i2400m_put(i2400m);
		kfree_skb(wake_tx_skb);
	}

	d_fnend(3, dev, "(i2400m %p) = void\n", i2400m);
}