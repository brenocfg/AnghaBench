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
struct r8192_priv {struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int capability; } ;
struct ieee80211_device {int wpa_ie_len; size_t tx_keyidx; int* wpa_ie; scalar_t__ host_encrypt; struct ieee80211_crypt_data** crypt; struct ieee80211_network current_network; } ;
struct ieee80211_crypt_data {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  ccmp_ie ; 
 int /*<<< orphan*/  ccmp_rsn_ie ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool GetNmodeSupportBySecCfg8192(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;
	struct ieee80211_network *network = &ieee->current_network;
	int wpa_ie_len = ieee->wpa_ie_len;
	struct ieee80211_crypt_data *crypt;
	int encrypt;

	crypt = ieee->crypt[ieee->tx_keyidx];
	/* we use connecting AP's capability instead of only security config
	 * on our driver to distinguish whether it should use N mode or G mode
	 */
	encrypt = (network->capability & WLAN_CAPABILITY_PRIVACY) ||
		  (ieee->host_encrypt && crypt && crypt->ops &&
		   (strcmp(crypt->ops->name, "WEP") == 0));

	/* simply judge  */
	if (encrypt && (wpa_ie_len == 0)) {
		/* wep encryption, no N mode setting */
		return false;
	} else if ((wpa_ie_len != 0)) {
		/* parse pairwise key type */
		if (((ieee->wpa_ie[0] == 0xdd) && (!memcmp(&(ieee->wpa_ie[14]), ccmp_ie, 4))) || ((ieee->wpa_ie[0] == 0x30) && (!memcmp(&ieee->wpa_ie[10], ccmp_rsn_ie, 4))))
			return true;
		else
			return false;
	} else {
		return true;
	}

	return true;
}