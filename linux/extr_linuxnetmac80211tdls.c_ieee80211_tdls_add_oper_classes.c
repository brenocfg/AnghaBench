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
typedef  void* u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chandef; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_SUPPORTED_REGULATORY_CLASSES ; 
 int /*<<< orphan*/  ieee80211_chandef_to_operating_class (int /*<<< orphan*/ *,void**) ; 
 void** skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ieee80211_tdls_add_oper_classes(struct ieee80211_sub_if_data *sdata,
					    struct sk_buff *skb)
{
	u8 *pos;
	u8 op_class;

	if (!ieee80211_chandef_to_operating_class(&sdata->vif.bss_conf.chandef,
						  &op_class))
		return;

	pos = skb_put(skb, 4);
	*pos++ = WLAN_EID_SUPPORTED_REGULATORY_CLASSES;
	*pos++ = 2; /* len */

	*pos++ = op_class;
	*pos++ = op_class; /* give current operating class as alternate too */
}