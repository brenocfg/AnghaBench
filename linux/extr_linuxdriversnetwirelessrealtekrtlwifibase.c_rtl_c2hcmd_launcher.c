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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  c2hcmd_lock; } ;
struct rtl_priv {TYPE_1__ locks; int /*<<< orphan*/  c2hcmd_queue; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_c2h_content_parsing (struct ieee80211_hw*,struct sk_buff*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl_c2hcmd_launcher(struct ieee80211_hw *hw, int exec)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct sk_buff *skb;
	unsigned long flags;
	int i;

	for (i = 0; i < 200; i++) {
		/* dequeue a task */
		spin_lock_irqsave(&rtlpriv->locks.c2hcmd_lock, flags);

		skb = __skb_dequeue(&rtlpriv->c2hcmd_queue);

		spin_unlock_irqrestore(&rtlpriv->locks.c2hcmd_lock, flags);

		/* do it */
		if (!skb)
			break;

		RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG, "C2H rx_desc_shift=%d\n",
			 *((u8 *)skb->cb));
		RT_PRINT_DATA(rtlpriv, COMP_FW, DBG_DMESG,
			      "C2H data: ", skb->data, skb->len);

		if (exec)
			rtl_c2h_content_parsing(hw, skb);

		/* free */
		dev_kfree_skb_any(skb);
	}
}