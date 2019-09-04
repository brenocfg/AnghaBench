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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rtl_desc_qsel { ____Placeholder_rtl_desc_qsel } rtl_desc_qsel ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_USB ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int QSLT_BE ; 
 int QSLT_BEACON ; 
 int QSLT_BK ; 
 int QSLT_MGNT ; 
 int QSLT_VI ; 
 int QSLT_VO ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rtl_desc_qsel _rtl8192cu_mq_to_descq(struct ieee80211_hw *hw,
					 __le16 fc, u16 mac80211_queue_index)
{
	enum rtl_desc_qsel qsel;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (unlikely(ieee80211_is_beacon(fc))) {
		qsel = QSLT_BEACON;
		goto out;
	}
	if (ieee80211_is_mgmt(fc)) {
		qsel = QSLT_MGNT;
		goto out;
	}
	switch (mac80211_queue_index) {
	case 0:	/* VO */
		qsel = QSLT_VO;
		RT_TRACE(rtlpriv, COMP_USB, DBG_DMESG,
			 "VO queue, set qsel = 0x%x\n", QSLT_VO);
		break;
	case 1:	/* VI */
		qsel = QSLT_VI;
		RT_TRACE(rtlpriv, COMP_USB, DBG_DMESG,
			 "VI queue, set qsel = 0x%x\n", QSLT_VI);
		break;
	case 3:	/* BK */
		qsel = QSLT_BK;
		RT_TRACE(rtlpriv, COMP_USB, DBG_DMESG,
			 "BK queue, set qsel = 0x%x\n", QSLT_BK);
		break;
	case 2:	/* BE */
	default:
		qsel = QSLT_BE;
		RT_TRACE(rtlpriv, COMP_USB, DBG_DMESG,
			 "BE queue, set qsel = 0x%x\n", QSLT_BE);
		break;
	}
out:
	return qsel;
}