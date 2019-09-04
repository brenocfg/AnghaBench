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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  c2hcmd_wq; int /*<<< orphan*/  rtl_wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  c2hcmd_lock; } ;
struct rtl_priv {TYPE_1__ works; TYPE_2__ locks; int /*<<< orphan*/  c2hcmd_queue; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_c2h_content_parsing (struct ieee80211_hw*,struct sk_buff*) ; 
 scalar_t__ rtl_c2h_fast_cmd (struct ieee80211_hw*,struct sk_buff*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl_c2hcmd_enqueue(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	unsigned long flags;

	if (rtl_c2h_fast_cmd(hw, skb)) {
		rtl_c2h_content_parsing(hw, skb);
		kfree_skb(skb);
		return;
	}

	/* enqueue */
	spin_lock_irqsave(&rtlpriv->locks.c2hcmd_lock, flags);

	__skb_queue_tail(&rtlpriv->c2hcmd_queue, skb);

	spin_unlock_irqrestore(&rtlpriv->locks.c2hcmd_lock, flags);

	/* wake up wq */
	queue_delayed_work(rtlpriv->works.rtl_wq, &rtlpriv->works.c2hcmd_wq, 0);
}