#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct key_params {int cipher; int seq_len; scalar_t__ seq; int /*<<< orphan*/  key_len; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int flags; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_EXT_KEY_ID ; 
 int /*<<< orphan*/  NL80211_KEY_NO_TX ; 
 int /*<<< orphan*/  NL80211_KEY_RX_TX ; 
 int /*<<< orphan*/  NL80211_KEY_SET_TX ; 
 int WIPHY_FLAG_IBSS_RSN ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 138 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 137 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 136 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 135 
#define  WLAN_CIPHER_SUITE_CCMP 134 
#define  WLAN_CIPHER_SUITE_CCMP_256 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  WLAN_KEY_LEN_AES_CMAC ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_BIP_CMAC_256 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_BIP_GMAC_128 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_BIP_GMAC_256 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_CCMP ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_CCMP_256 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_GCMP ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_GCMP_256 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_TKIP ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_WEP104 ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_WEP40 ; 
 int /*<<< orphan*/  cfg80211_supported_cipher_suite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (TYPE_1__*,int /*<<< orphan*/ ) ; 

int cfg80211_validate_key_settings(struct cfg80211_registered_device *rdev,
				   struct key_params *params, int key_idx,
				   bool pairwise, const u8 *mac_addr)
{
	if (key_idx < 0 || key_idx > 5)
		return -EINVAL;

	if (!pairwise && mac_addr && !(rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN))
		return -EINVAL;

	if (pairwise && !mac_addr)
		return -EINVAL;

	switch (params->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
		/* Extended Key ID can only be used with CCMP/GCMP ciphers */
		if ((pairwise && key_idx) ||
		    params->mode != NL80211_KEY_RX_TX)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		/* IEEE802.11-2016 allows only 0 and - when supporting
		 * Extended Key ID - 1 as index for pairwise keys.
		 * @NL80211_KEY_NO_TX is only allowed for pairwise keys when
		 * the driver supports Extended Key ID.
		 * @NL80211_KEY_SET_TX can't be set when installing and
		 * validating a key.
		 */
		if ((params->mode == NL80211_KEY_NO_TX && !pairwise) ||
		    params->mode == NL80211_KEY_SET_TX)
			return -EINVAL;
		if (wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_EXT_KEY_ID)) {
			if (pairwise && (key_idx < 0 || key_idx > 1))
				return -EINVAL;
		} else if (pairwise && key_idx) {
			return -EINVAL;
		}
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
		/* Disallow BIP (group-only) cipher as pairwise cipher */
		if (pairwise)
			return -EINVAL;
		if (key_idx < 4)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		if (key_idx > 3)
			return -EINVAL;
	default:
		break;
	}

	switch (params->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
		if (params->key_len != WLAN_KEY_LEN_WEP40)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		if (params->key_len != WLAN_KEY_LEN_TKIP)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		if (params->key_len != WLAN_KEY_LEN_CCMP)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_CCMP_256:
		if (params->key_len != WLAN_KEY_LEN_CCMP_256)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_GCMP:
		if (params->key_len != WLAN_KEY_LEN_GCMP)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_GCMP_256:
		if (params->key_len != WLAN_KEY_LEN_GCMP_256)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		if (params->key_len != WLAN_KEY_LEN_WEP104)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
		if (params->key_len != WLAN_KEY_LEN_AES_CMAC)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
		if (params->key_len != WLAN_KEY_LEN_BIP_CMAC_256)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
		if (params->key_len != WLAN_KEY_LEN_BIP_GMAC_128)
			return -EINVAL;
		break;
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
		if (params->key_len != WLAN_KEY_LEN_BIP_GMAC_256)
			return -EINVAL;
		break;
	default:
		/*
		 * We don't know anything about this algorithm,
		 * allow using it -- but the driver must check
		 * all parameters! We still check below whether
		 * or not the driver supports this algorithm,
		 * of course.
		 */
		break;
	}

	if (params->seq) {
		switch (params->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			/* These ciphers do not use key sequence */
			return -EINVAL;
		case WLAN_CIPHER_SUITE_TKIP:
		case WLAN_CIPHER_SUITE_CCMP:
		case WLAN_CIPHER_SUITE_CCMP_256:
		case WLAN_CIPHER_SUITE_GCMP:
		case WLAN_CIPHER_SUITE_GCMP_256:
		case WLAN_CIPHER_SUITE_AES_CMAC:
		case WLAN_CIPHER_SUITE_BIP_CMAC_256:
		case WLAN_CIPHER_SUITE_BIP_GMAC_128:
		case WLAN_CIPHER_SUITE_BIP_GMAC_256:
			if (params->seq_len != 6)
				return -EINVAL;
			break;
		}
	}

	if (!cfg80211_supported_cipher_suite(&rdev->wiphy, params->cipher))
		return -EINVAL;

	return 0;
}