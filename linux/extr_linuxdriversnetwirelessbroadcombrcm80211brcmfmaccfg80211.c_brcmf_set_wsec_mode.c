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
struct net_device {int dummy; } ;
struct TYPE_2__ {int* ciphers_pairwise; int cipher_group; scalar_t__ n_ciphers_pairwise; } ;
struct cfg80211_connect_params {TYPE_1__ crypto; scalar_t__ privacy; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; } ;
struct brcmf_cfg80211_security {int cipher_pairwise; int cipher_group; } ;
struct brcmf_cfg80211_profile {struct brcmf_cfg80211_security sec; } ;
typedef  int s32 ;

/* Variables and functions */
 int AES_ENABLED ; 
 int /*<<< orphan*/  CONN ; 
 int EINVAL ; 
 int TKIP_ENABLED ; 
 int WEP_ENABLED ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int brcmf_fil_bsscfg_int_set (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ brcmf_find_wpsie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_cfg80211_profile* ndev_to_prof (struct net_device*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32
brcmf_set_wsec_mode(struct net_device *ndev,
		    struct cfg80211_connect_params *sme)
{
	struct brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	struct brcmf_cfg80211_security *sec;
	s32 pval = 0;
	s32 gval = 0;
	s32 wsec;
	s32 err = 0;

	if (sme->crypto.n_ciphers_pairwise) {
		switch (sme->crypto.ciphers_pairwise[0]) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			pval = WEP_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			pval = TKIP_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			pval = AES_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_AES_CMAC:
			pval = AES_ENABLED;
			break;
		default:
			brcmf_err("invalid cipher pairwise (%d)\n",
				  sme->crypto.ciphers_pairwise[0]);
			return -EINVAL;
		}
	}
	if (sme->crypto.cipher_group) {
		switch (sme->crypto.cipher_group) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			gval = WEP_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			gval = TKIP_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			gval = AES_ENABLED;
			break;
		case WLAN_CIPHER_SUITE_AES_CMAC:
			gval = AES_ENABLED;
			break;
		default:
			brcmf_err("invalid cipher group (%d)\n",
				  sme->crypto.cipher_group);
			return -EINVAL;
		}
	}

	brcmf_dbg(CONN, "pval (%d) gval (%d)\n", pval, gval);
	/* In case of privacy, but no security and WPS then simulate */
	/* setting AES. WPS-2.0 allows no security                   */
	if (brcmf_find_wpsie(sme->ie, sme->ie_len) && !pval && !gval &&
	    sme->privacy)
		pval = AES_ENABLED;

	wsec = pval | gval;
	err = brcmf_fil_bsscfg_int_set(netdev_priv(ndev), "wsec", wsec);
	if (err) {
		brcmf_err("error (%d)\n", err);
		return err;
	}

	sec = &profile->sec;
	sec->cipher_pairwise = sme->crypto.ciphers_pairwise[0];
	sec->cipher_group = sme->crypto.cipher_group;

	return err;
}