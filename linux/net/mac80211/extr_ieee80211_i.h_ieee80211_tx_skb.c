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
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_tx_skb_tid (struct ieee80211_sub_if_data*,struct sk_buff*,int) ; 

__attribute__((used)) static inline void ieee80211_tx_skb(struct ieee80211_sub_if_data *sdata,
				    struct sk_buff *skb)
{
	/* Send all internal mgmt frames on VO. Accordingly set TID to 7. */
	ieee80211_tx_skb_tid(sdata, skb, 7);
}