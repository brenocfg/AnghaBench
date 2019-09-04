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
typedef  int /*<<< orphan*/  u8 ;
struct key_params {int cipher; int seq_len; scalar_t__ seq; int /*<<< orphan*/  key_len; } ;
struct TYPE_2__ {int flags; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;

/* Variables and functions */
 int EINVAL ; 
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
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		/* Disallow pairwise keys with non-zero index unless it's WEP
		 * or a vendor specific cipher (because current deployments use
		 * pairwise WEP keys with non-zero indices and for vendor
		 * specific ciphers this should be validated in the driver or
		 * hardware level - but 802.11i clearly specifies to use zero)
		 */
		if (pairwise && key_idx)
			return -EINVAL;
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