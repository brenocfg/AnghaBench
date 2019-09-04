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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct mac_iveiv_entry {int /*<<< orphan*/ * iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  iv32; int /*<<< orphan*/  iv16; } ;
struct ieee80211_key_seq {TYPE_1__ tkip; } ;
struct ieee80211_key_conf {scalar_t__ cipher; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
typedef  int /*<<< orphan*/  iveiv_entry ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_IVEIV_ENTRY (int /*<<< orphan*/ ) ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt2800_register_multiread (struct rt2x00_dev*,int /*<<< orphan*/ ,struct mac_iveiv_entry*,int) ; 

void rt2800_get_key_seq(struct ieee80211_hw *hw,
			struct ieee80211_key_conf *key,
			struct ieee80211_key_seq *seq)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct mac_iveiv_entry iveiv_entry;
	u32 offset;

	if (key->cipher != WLAN_CIPHER_SUITE_TKIP)
		return;

	offset = MAC_IVEIV_ENTRY(key->hw_key_idx);
	rt2800_register_multiread(rt2x00dev, offset,
				      &iveiv_entry, sizeof(iveiv_entry));

	memcpy(&seq->tkip.iv16, &iveiv_entry.iv[0], 2);
	memcpy(&seq->tkip.iv32, &iveiv_entry.iv[4], 4);
}