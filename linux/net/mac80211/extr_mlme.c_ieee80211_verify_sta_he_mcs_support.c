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
typedef  int u8 ;
typedef  int u16 ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_he_mcs_nss_supp {int dummy; } ;
struct ieee80211_sta_he_cap {struct ieee80211_he_mcs_nss_supp he_mcs_nss_supp; } ;
struct ieee80211_he_operation {int /*<<< orphan*/  he_mcs_nss_set; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IEEE80211_HE_MCS_NOT_SUPPORTED ; 
 struct ieee80211_sta_he_cap* ieee80211_get_he_sta_cap (struct ieee80211_supported_band*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ieee80211_verify_sta_he_mcs_support(struct ieee80211_supported_band *sband,
				    const struct ieee80211_he_operation *he_op)
{
	const struct ieee80211_sta_he_cap *sta_he_cap =
		ieee80211_get_he_sta_cap(sband);
	u16 ap_min_req_set;
	int i;

	if (!sta_he_cap || !he_op)
		return false;

	ap_min_req_set = le16_to_cpu(he_op->he_mcs_nss_set);

	/* Need to go over for 80MHz, 160MHz and for 80+80 */
	for (i = 0; i < 3; i++) {
		const struct ieee80211_he_mcs_nss_supp *sta_mcs_nss_supp =
			&sta_he_cap->he_mcs_nss_supp;
		u16 sta_mcs_map_rx =
			le16_to_cpu(((__le16 *)sta_mcs_nss_supp)[2 * i]);
		u16 sta_mcs_map_tx =
			le16_to_cpu(((__le16 *)sta_mcs_nss_supp)[2 * i + 1]);
		u8 nss;
		bool verified = true;

		/*
		 * For each band there is a maximum of 8 spatial streams
		 * possible. Each of the sta_mcs_map_* is a 16-bit struct built
		 * of 2 bits per NSS (1-8), with the values defined in enum
		 * ieee80211_he_mcs_support. Need to make sure STA TX and RX
		 * capabilities aren't less than the AP's minimum requirements
		 * for this HE BSS per SS.
		 * It is enough to find one such band that meets the reqs.
		 */
		for (nss = 8; nss > 0; nss--) {
			u8 sta_rx_val = (sta_mcs_map_rx >> (2 * (nss - 1))) & 3;
			u8 sta_tx_val = (sta_mcs_map_tx >> (2 * (nss - 1))) & 3;
			u8 ap_val = (ap_min_req_set >> (2 * (nss - 1))) & 3;

			if (ap_val == IEEE80211_HE_MCS_NOT_SUPPORTED)
				continue;

			/*
			 * Make sure the HE AP doesn't require MCSs that aren't
			 * supported by the client
			 */
			if (sta_rx_val == IEEE80211_HE_MCS_NOT_SUPPORTED ||
			    sta_tx_val == IEEE80211_HE_MCS_NOT_SUPPORTED ||
			    (ap_val > sta_rx_val) || (ap_val > sta_tx_val)) {
				verified = false;
				break;
			}
		}

		if (verified)
			return true;
	}

	/* If here, STA doesn't meet AP's HE min requirements */
	return false;
}