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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_sta_node {int is_11n_enabled; int /*<<< orphan*/  max_amsdu; } ;
struct mwifiex_private {int dummy; } ;
struct ieee_types_header {int dummy; } ;
struct ieee80211_ht_cap {int /*<<< orphan*/  cap_info; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  MWIFIEX_TX_DATA_BUF_SIZE_4K ; 
 int /*<<< orphan*/  MWIFIEX_TX_DATA_BUF_SIZE_8K ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 scalar_t__ cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void
mwifiex_set_sta_ht_cap(struct mwifiex_private *priv, const u8 *ies,
		       int ies_len, struct mwifiex_sta_node *node)
{
	struct ieee_types_header *ht_cap_ie;
	const struct ieee80211_ht_cap *ht_cap;

	if (!ies)
		return;

	ht_cap_ie = (void *)cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, ies,
					     ies_len);
	if (ht_cap_ie) {
		ht_cap = (void *)(ht_cap_ie + 1);
		node->is_11n_enabled = 1;
		node->max_amsdu = le16_to_cpu(ht_cap->cap_info) &
				  IEEE80211_HT_CAP_MAX_AMSDU ?
				  MWIFIEX_TX_DATA_BUF_SIZE_8K :
				  MWIFIEX_TX_DATA_BUF_SIZE_4K;
	} else {
		node->is_11n_enabled = 0;
	}

	return;
}