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
struct mwifiex_bssdescriptor {int /*<<< orphan*/  bcn_vht_cap; struct ieee80211_vht_operation* bcn_vht_oper; } ;
struct TYPE_2__ {struct mwifiex_bssdescriptor bss_descriptor; } ;
struct mwifiex_private {TYPE_1__ curr_bss_params; } ;
struct ieee80211_vht_operation {scalar_t__ chan_width; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_VHT_CHANWIDTH_USE_HT ; 

bool mwifiex_is_bss_in_11ac_mode(struct mwifiex_private *priv)
{
	struct mwifiex_bssdescriptor *bss_desc;
	struct ieee80211_vht_operation *vht_oper;

	bss_desc = &priv->curr_bss_params.bss_descriptor;
	vht_oper = bss_desc->bcn_vht_oper;

	if (!bss_desc->bcn_vht_cap || !vht_oper)
		return false;

	if (vht_oper->chan_width == IEEE80211_VHT_CHANWIDTH_USE_HT)
		return false;

	return true;
}