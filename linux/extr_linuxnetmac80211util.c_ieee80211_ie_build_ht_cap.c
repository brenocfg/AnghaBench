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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sta_ht_cap {int ampdu_factor; int ampdu_density; int /*<<< orphan*/  mcs; } ;
struct ieee80211_ht_cap {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u8 *ieee80211_ie_build_ht_cap(u8 *pos, struct ieee80211_sta_ht_cap *ht_cap,
			      u16 cap)
{
	__le16 tmp;

	*pos++ = WLAN_EID_HT_CAPABILITY;
	*pos++ = sizeof(struct ieee80211_ht_cap);
	memset(pos, 0, sizeof(struct ieee80211_ht_cap));

	/* capability flags */
	tmp = cpu_to_le16(cap);
	memcpy(pos, &tmp, sizeof(u16));
	pos += sizeof(u16);

	/* AMPDU parameters */
	*pos++ = ht_cap->ampdu_factor |
		 (ht_cap->ampdu_density <<
			IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT);

	/* MCS set */
	memcpy(pos, &ht_cap->mcs, sizeof(ht_cap->mcs));
	pos += sizeof(ht_cap->mcs);

	/* extended capabilities */
	pos += sizeof(__le16);

	/* BF capabilities */
	pos += sizeof(__le32);

	/* antenna selection */
	pos += sizeof(u8);

	return pos;
}