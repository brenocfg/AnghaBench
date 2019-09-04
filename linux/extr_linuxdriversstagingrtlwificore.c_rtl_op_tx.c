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
struct sk_buff {int dummy; } ;
struct rtl_tcb_desc {int dummy; } ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct rtl_priv {TYPE_1__* intf_ops; int /*<<< orphan*/  status; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* adapter_tx ) (struct ieee80211_hw*,int /*<<< orphan*/ ,struct sk_buff*,struct rtl_tcb_desc*) ;int /*<<< orphan*/  (* waitq_insert ) (struct ieee80211_hw*,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  RTL_STATUS_INTERFACE_START ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  memset (struct rtl_tcb_desc*,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,struct sk_buff*,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rtl_op_tx(struct ieee80211_hw *hw,
		      struct ieee80211_tx_control *control,
		      struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_tcb_desc tcb_desc;

	memset(&tcb_desc, 0, sizeof(struct rtl_tcb_desc));

	if (unlikely(is_hal_stop(rtlhal) || ppsc->rfpwr_state != ERFON))
		goto err_free;

	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		goto err_free;

	if (!rtlpriv->intf_ops->waitq_insert(hw, control->sta, skb))
		rtlpriv->intf_ops->adapter_tx(hw, control->sta, skb, &tcb_desc);
	return;

err_free:
	dev_kfree_skb_any(skb);
}