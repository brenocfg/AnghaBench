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
typedef  size_t u8 ;
typedef  int u16 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {int /*<<< orphan*/ * wep_key; int /*<<< orphan*/ * wep_key_len; struct net_device* mesh_dev; } ;
struct key_params {int cipher; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  seq_len; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 int KEY_INFO_WPA_ENABLED ; 
 int KEY_INFO_WPA_MCAST ; 
 int KEY_INFO_WPA_UNICAST ; 
 int KEY_TYPE_ID_AES ; 
 int KEY_TYPE_ID_TKIP ; 
 int /*<<< orphan*/  LBS_DEB_CFG80211 ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  lbs_deb_assoc (char*,int,...) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_set_key_material (struct lbs_private*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_set_wep_keys (struct lbs_private*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (struct wiphy*,char*,int const) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_add_key(struct wiphy *wiphy, struct net_device *netdev,
			   u8 idx, bool pairwise, const u8 *mac_addr,
			   struct key_params *params)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	u16 key_info;
	u16 key_type;
	int ret = 0;

	if (netdev == priv->mesh_dev)
		return -EOPNOTSUPP;

	lbs_deb_assoc("add_key: cipher 0x%x, mac_addr %pM\n",
		      params->cipher, mac_addr);
	lbs_deb_assoc("add_key: key index %d, key len %d\n",
		      idx, params->key_len);
	if (params->key_len)
		lbs_deb_hex(LBS_DEB_CFG80211, "KEY",
			    params->key, params->key_len);

	lbs_deb_assoc("add_key: seq len %d\n", params->seq_len);
	if (params->seq_len)
		lbs_deb_hex(LBS_DEB_CFG80211, "SEQ",
			    params->seq, params->seq_len);

	switch (params->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		/* actually compare if something has changed ... */
		if ((priv->wep_key_len[idx] != params->key_len) ||
			memcmp(priv->wep_key[idx],
			       params->key, params->key_len) != 0) {
			priv->wep_key_len[idx] = params->key_len;
			memcpy(priv->wep_key[idx],
			       params->key, params->key_len);
			lbs_set_wep_keys(priv);
		}
		break;
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
		key_info = KEY_INFO_WPA_ENABLED | ((idx == 0)
						   ? KEY_INFO_WPA_UNICAST
						   : KEY_INFO_WPA_MCAST);
		key_type = (params->cipher == WLAN_CIPHER_SUITE_TKIP)
			? KEY_TYPE_ID_TKIP
			: KEY_TYPE_ID_AES;
		lbs_set_key_material(priv,
				     key_type,
				     key_info,
				     params->key, params->key_len);
		break;
	default:
		wiphy_err(wiphy, "unhandled cipher 0x%x\n", params->cipher);
		ret = -ENOTSUPP;
		break;
	}

	return ret;
}