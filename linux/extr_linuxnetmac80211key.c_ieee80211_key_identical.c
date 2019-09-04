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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;
struct TYPE_4__ {int keylen; scalar_t__ cipher; int flags; int /*<<< orphan*/ * key; } ;
struct ieee80211_key {TYPE_2__ conf; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int WLAN_KEY_LEN_TKIP ; 
 int /*<<< orphan*/  crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool ieee80211_key_identical(struct ieee80211_sub_if_data *sdata,
				    struct ieee80211_key *old,
				    struct ieee80211_key *new)
{
	u8 tkip_old[WLAN_KEY_LEN_TKIP], tkip_new[WLAN_KEY_LEN_TKIP];
	u8 *tk_old, *tk_new;

	if (!old || new->conf.keylen != old->conf.keylen)
		return false;

	tk_old = old->conf.key;
	tk_new = new->conf.key;

	/*
	 * In station mode, don't compare the TX MIC key, as it's never used
	 * and offloaded rekeying may not care to send it to the host. This
	 * is the case in iwlwifi, for example.
	 */
	if (sdata->vif.type == NL80211_IFTYPE_STATION &&
	    new->conf.cipher == WLAN_CIPHER_SUITE_TKIP &&
	    new->conf.keylen == WLAN_KEY_LEN_TKIP &&
	    !(new->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
		memcpy(tkip_old, tk_old, WLAN_KEY_LEN_TKIP);
		memcpy(tkip_new, tk_new, WLAN_KEY_LEN_TKIP);
		memset(tkip_old + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		memset(tkip_new + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		tk_old = tkip_old;
		tk_new = tkip_new;
	}

	return !crypto_memneq(tk_old, tk_new, new->conf.keylen);
}