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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_vht_cap {int dummy; } ;
struct ieee80211_sta_vht_cap {int /*<<< orphan*/  vht_mcs; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u8 *ieee80211_ie_build_vht_cap(u8 *pos, struct ieee80211_sta_vht_cap *vht_cap,
			       u32 cap)
{
	__le32 tmp;

	*pos++ = WLAN_EID_VHT_CAPABILITY;
	*pos++ = sizeof(struct ieee80211_vht_cap);
	memset(pos, 0, sizeof(struct ieee80211_vht_cap));

	/* capability flags */
	tmp = cpu_to_le32(cap);
	memcpy(pos, &tmp, sizeof(u32));
	pos += sizeof(u32);

	/* VHT MCS set */
	memcpy(pos, &vht_cap->vht_mcs, sizeof(vht_cap->vht_mcs));
	pos += sizeof(vht_cap->vht_mcs);

	return pos;
}