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
struct TYPE_2__ {int /*<<< orphan*/  ips_nic_off_wq; int /*<<< orphan*/  rtl_wq; } ;
struct rtl_priv {TYPE_1__ works; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSECS (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_ips_nic_off(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	/* because when link with ap, mac80211 will ask us
	 * to disable nic quickly after scan before linking,
	 * this will cause link failed, so we delay 100ms here
	 */
	queue_delayed_work(rtlpriv->works.rtl_wq,
			   &rtlpriv->works.ips_nic_off_wq, MSECS(100));
}