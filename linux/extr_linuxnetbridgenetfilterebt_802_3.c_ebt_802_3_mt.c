#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_action_param {struct ebt_802_3_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ebt_802_3_info {int bitmask; scalar_t__ sap; scalar_t__ type; } ;
struct TYPE_5__ {int ctrl; scalar_t__ type; scalar_t__ ssap; scalar_t__ dsap; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_2__ ui; TYPE_1__ ni; } ;
struct ebt_802_3_hdr {TYPE_3__ llc; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ CHECK_TYPE ; 
 int EBT_802_3_SAP ; 
 int EBT_802_3_TYPE ; 
 int IS_UI ; 
 scalar_t__ NF_INVF (struct ebt_802_3_info const*,int,int) ; 
 struct ebt_802_3_hdr* ebt_802_3_hdr (struct sk_buff const*) ; 

__attribute__((used)) static bool
ebt_802_3_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ebt_802_3_info *info = par->matchinfo;
	const struct ebt_802_3_hdr *hdr = ebt_802_3_hdr(skb);
	__be16 type = hdr->llc.ui.ctrl & IS_UI ? hdr->llc.ui.type : hdr->llc.ni.type;

	if (info->bitmask & EBT_802_3_SAP) {
		if (NF_INVF(info, EBT_802_3_SAP, info->sap != hdr->llc.ui.ssap))
			return false;
		if (NF_INVF(info, EBT_802_3_SAP, info->sap != hdr->llc.ui.dsap))
			return false;
	}

	if (info->bitmask & EBT_802_3_TYPE) {
		if (!(hdr->llc.ui.dsap == CHECK_TYPE && hdr->llc.ui.ssap == CHECK_TYPE))
			return false;
		if (NF_INVF(info, EBT_802_3_TYPE, info->type != type))
			return false;
	}

	return true;
}