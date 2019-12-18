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
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_he_operation {int /*<<< orphan*/  he_mcs_nss_set; int /*<<< orphan*/  he_oper_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_BSS_COLOR_DISABLED ; 
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_ER_SU_DISABLE ; 
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK ; 
 int /*<<< orphan*/  WLAN_EID_EXTENSION ; 
 int /*<<< orphan*/  WLAN_EID_EXT_HE_OPERATION ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_encode_bits (int,int /*<<< orphan*/ ) ; 

u8 *ieee80211_ie_build_he_oper(u8 *pos)
{
	struct ieee80211_he_operation *he_oper;
	u32 he_oper_params;

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + sizeof(struct ieee80211_he_operation);
	*pos++ = WLAN_EID_EXT_HE_OPERATION;

	he_oper_params = 0;
	he_oper_params |= u32_encode_bits(1023, /* disabled */
				IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK);
	he_oper_params |= u32_encode_bits(1,
				IEEE80211_HE_OPERATION_ER_SU_DISABLE);
	he_oper_params |= u32_encode_bits(1,
				IEEE80211_HE_OPERATION_BSS_COLOR_DISABLED);

	he_oper = (struct ieee80211_he_operation *)pos;
	he_oper->he_oper_params = cpu_to_le32(he_oper_params);

	/* don't require special HE peer rates */
	he_oper->he_mcs_nss_set = cpu_to_le16(0xffff);

	/* TODO add VHT operational and 6GHz operational subelement? */

	return pos + sizeof(struct ieee80211_vht_operation);
}