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
struct TYPE_2__ {void* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct fq_tin {int dummy; } ;
struct fq_flow {int dummy; } ;
struct fq {int dummy; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static bool fq_vlan_filter_func(struct fq *fq, struct fq_tin *tin,
				struct fq_flow *flow, struct sk_buff *skb,
				void *data)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	return info->control.vif == data;
}