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
typedef  int u8 ;
struct sk_buff {int priority; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int QSLT_BEACON ; 
 int QSLT_HIGH ; 
 int QSLT_MGNT ; 
 int QSLT_VO ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 _rtl92se_map_hwqueue_to_fwqueue(struct sk_buff *skb,	u8 skb_queue)
{
	__le16 fc = rtl_get_fc(skb);

	if (unlikely(ieee80211_is_beacon(fc)))
		return QSLT_BEACON;
	if (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		return QSLT_MGNT;
	if (ieee80211_is_nullfunc(fc))
		return QSLT_HIGH;

	/* Kernel commit 1bf4bbb4024dcdab changed EAPOL packets to use
	 * queue V0 at priority 7; however, the RTL8192SE appears to have
	 * that queue at priority 6
	 */
	if (skb->priority == 7)
		return QSLT_VO;
	return skb->priority;
}