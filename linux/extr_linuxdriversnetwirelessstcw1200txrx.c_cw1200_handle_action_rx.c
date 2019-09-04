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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ category; } ;
struct TYPE_4__ {TYPE_1__ action; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ WLAN_CATEGORY_BACK ; 

__attribute__((used)) static int cw1200_handle_action_rx(struct cw1200_common *priv,
				   struct sk_buff *skb)
{
	struct ieee80211_mgmt *mgmt = (void *)skb->data;

	/* Filter block ACK negotiation: fully controlled by firmware */
	if (mgmt->u.action.category == WLAN_CATEGORY_BACK)
		return 1;

	return 0;
}