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
typedef  int /*<<< orphan*/  wpa_suite ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wpa_suite {void* rsn_capability; int /*<<< orphan*/  rsn_mode; void* size; struct wpa_suite** suite; } ;
struct rsn_mode {void* rsn_capability; int /*<<< orphan*/  rsn_mode; void* size; struct rsn_mode** suite; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  rsn_enabled; int /*<<< orphan*/  key_mgmt_suite; int /*<<< orphan*/  group_suite; int /*<<< orphan*/  pairwise_suite; } ;
struct ks_wlan_private {TYPE_1__ wpa; } ;
typedef  int /*<<< orphan*/  rsn_mode ;

/* Variables and functions */
 int CIPHER_ID_LEN ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA2_CCMP ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA2_NONE ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA2_TKIP ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA2_WEP104 ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA2_WEP40 ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA_CCMP ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA_NONE ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA_TKIP ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA_WEP104 ; 
 int /*<<< orphan*/ * CIPHER_ID_WPA_WEP40 ; 
 int /*<<< orphan*/  DOT11_RSN_CONFIG_AUTH_SUITE ; 
 int /*<<< orphan*/  DOT11_RSN_CONFIG_MULTICAST_CIPHER ; 
 int /*<<< orphan*/  DOT11_RSN_CONFIG_UNICAST_CIPHER ; 
 int /*<<< orphan*/  DOT11_RSN_ENABLED ; 
#define  IW_AUTH_CIPHER_CCMP 139 
#define  IW_AUTH_CIPHER_NONE 138 
#define  IW_AUTH_CIPHER_TKIP 137 
#define  IW_AUTH_CIPHER_WEP104 136 
#define  IW_AUTH_CIPHER_WEP40 135 
#define  IW_AUTH_KEY_MGMT_802_1X 134 
#define  IW_AUTH_KEY_MGMT_PSK 133 
 int /*<<< orphan*/  IW_AUTH_WPA_VERSION_WPA ; 
 int /*<<< orphan*/  IW_AUTH_WPA_VERSION_WPA2 ; 
 int KEY_MGMT_ID_LEN ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA2_1X ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA2_NONE ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA2_PSK ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA2_WPANONE ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA_1X ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA_NONE ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA_PSK ; 
 int /*<<< orphan*/ * KEY_MGMT_ID_WPA_WPANONE ; 
 int /*<<< orphan*/  LOCAL_RSN_MODE ; 
 int /*<<< orphan*/  RSN_MODE_NONE ; 
 int /*<<< orphan*/  RSN_MODE_WPA ; 
 int /*<<< orphan*/  RSN_MODE_WPA2 ; 
#define  SME_RSN_AUTH_REQUEST 132 
#define  SME_RSN_ENABLED_REQUEST 131 
#define  SME_RSN_MCAST_REQUEST 130 
#define  SME_RSN_MODE_REQUEST 129 
#define  SME_RSN_UCAST_REQUEST 128 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_bool (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_ostring (struct ks_wlan_private*,int /*<<< orphan*/ ,struct wpa_suite*,int) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (struct wpa_suite*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct wpa_suite*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hostif_sme_set_rsn(struct ks_wlan_private *priv, int type)
{
	struct wpa_suite wpa_suite;
	struct rsn_mode rsn_mode;
	size_t size;
	u32 mode;
	const u8 *buf = NULL;

	memset(&wpa_suite, 0, sizeof(wpa_suite));

	switch (type) {
	case SME_RSN_UCAST_REQUEST:
		wpa_suite.size = cpu_to_le16(1);
		switch (priv->wpa.pairwise_suite) {
		case IW_AUTH_CIPHER_NONE:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_NONE : CIPHER_ID_WPA_NONE;
			break;
		case IW_AUTH_CIPHER_WEP40:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP40 : CIPHER_ID_WPA_WEP40;
			break;
		case IW_AUTH_CIPHER_TKIP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_TKIP : CIPHER_ID_WPA_TKIP;
			break;
		case IW_AUTH_CIPHER_CCMP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_CCMP : CIPHER_ID_WPA_CCMP;
			break;
		case IW_AUTH_CIPHER_WEP104:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP104 : CIPHER_ID_WPA_WEP104;
			break;
		}

		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, CIPHER_ID_LEN);
		size = sizeof(wpa_suite.size) +
		       (CIPHER_ID_LEN * le16_to_cpu(wpa_suite.size));
		hostif_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_UNICAST_CIPHER,
					       &wpa_suite, size);
		break;
	case SME_RSN_MCAST_REQUEST:
		switch (priv->wpa.group_suite) {
		case IW_AUTH_CIPHER_NONE:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_NONE : CIPHER_ID_WPA_NONE;
			break;
		case IW_AUTH_CIPHER_WEP40:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP40 : CIPHER_ID_WPA_WEP40;
			break;
		case IW_AUTH_CIPHER_TKIP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_TKIP : CIPHER_ID_WPA_TKIP;
			break;
		case IW_AUTH_CIPHER_CCMP:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_CCMP : CIPHER_ID_WPA_CCMP;
			break;
		case IW_AUTH_CIPHER_WEP104:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				CIPHER_ID_WPA2_WEP104 : CIPHER_ID_WPA_WEP104;
			break;
		}
		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, CIPHER_ID_LEN);
		hostif_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_MULTICAST_CIPHER,
					       &wpa_suite.suite[0][0],
					       CIPHER_ID_LEN);
		break;
	case SME_RSN_AUTH_REQUEST:
		wpa_suite.size = cpu_to_le16(1);
		switch (priv->wpa.key_mgmt_suite) {
		case IW_AUTH_KEY_MGMT_802_1X:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_1X : KEY_MGMT_ID_WPA_1X;
			break;
		case IW_AUTH_KEY_MGMT_PSK:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_PSK : KEY_MGMT_ID_WPA_PSK;
			break;
		case 0:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_NONE : KEY_MGMT_ID_WPA_NONE;
			break;
		case 4:
			buf = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
				KEY_MGMT_ID_WPA2_WPANONE :
				KEY_MGMT_ID_WPA_WPANONE;
			break;
		}

		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, KEY_MGMT_ID_LEN);
		size = sizeof(wpa_suite.size) +
		       (KEY_MGMT_ID_LEN * le16_to_cpu(wpa_suite.size));
		hostif_mib_set_request_ostring(priv,
					       DOT11_RSN_CONFIG_AUTH_SUITE,
					       &wpa_suite, size);
		break;
	case SME_RSN_ENABLED_REQUEST:
		hostif_mib_set_request_bool(priv, DOT11_RSN_ENABLED,
					    priv->wpa.rsn_enabled);
		break;
	case SME_RSN_MODE_REQUEST:
		mode = (priv->wpa.version == IW_AUTH_WPA_VERSION_WPA2) ?
			RSN_MODE_WPA2 :
			(priv->wpa.version == IW_AUTH_WPA_VERSION_WPA) ?
			 RSN_MODE_WPA : RSN_MODE_NONE;
		rsn_mode.rsn_mode = cpu_to_le32(mode);
		rsn_mode.rsn_capability = cpu_to_le16(0);
		hostif_mib_set_request_ostring(priv, LOCAL_RSN_MODE,
					       &rsn_mode, sizeof(rsn_mode));
		break;
	}
}