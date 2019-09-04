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
struct rtl_tx_report {int /*<<< orphan*/  queue; } ;
struct rtl_priv {struct rtl_tx_report tx_report; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_tx_ackqueue(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_tx_report *tx_report = &rtlpriv->tx_report;

	__skb_queue_tail(&tx_report->queue, skb);
}