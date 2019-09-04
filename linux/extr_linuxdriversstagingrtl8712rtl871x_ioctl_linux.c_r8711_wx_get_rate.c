#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int value; scalar_t__ fixed; } ;
union iwreq_data {TYPE_3__ bitrate; } ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct wlan_bssid_ex {int* rates; scalar_t__ IELength; int /*<<< orphan*/ * IEs; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct wlan_bssid_ex network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_ht_cap {int /*<<< orphan*/  cap_info; int /*<<< orphan*/  supp_mcs_set; } ;
struct TYPE_5__ {unsigned char rf_config; } ;
struct _adapter {TYPE_2__ registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int ENOLINK ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH ; 
 unsigned char RTL8712_RF_2T2R ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int _FW_LINKED ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int* r8712_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int r8711_wx_get_rate(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	struct ieee80211_ht_cap *pht_capie;
	unsigned char rf_type = padapter->registrypriv.rf_config;
	int i;
	u8 *p;
	u16 rate, max_rate = 0, ht_cap = false;
	u32 ht_ielen = 0;
	u8 bw_40MHz = 0, short_GI = 0;
	u16 mcs_rate = 0;

	i = 0;
	if (!check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE))
		return -ENOLINK;
	p = r8712_get_ie(&pcur_bss->IEs[12], _HT_CAPABILITY_IE_, &ht_ielen,
			 pcur_bss->IELength - 12);
	if (p && ht_ielen > 0) {
		ht_cap = true;
		pht_capie = (struct ieee80211_ht_cap *)(p + 2);
		memcpy(&mcs_rate, pht_capie->supp_mcs_set, 2);
		bw_40MHz = (le16_to_cpu(pht_capie->cap_info) &
			    IEEE80211_HT_CAP_SUP_WIDTH) ? 1 : 0;
		short_GI = (le16_to_cpu(pht_capie->cap_info) &
			    (IEEE80211_HT_CAP_SGI_20 |
			    IEEE80211_HT_CAP_SGI_40)) ? 1 : 0;
	}
	while ((pcur_bss->rates[i] != 0) &&
	       (pcur_bss->rates[i] != 0xFF)) {
		rate = pcur_bss->rates[i] & 0x7F;
		if (rate > max_rate)
			max_rate = rate;
		wrqu->bitrate.fixed = 0;	/* no auto select */
		wrqu->bitrate.value = rate * 500000;
		i++;
	}
	if (ht_cap) {
		if (mcs_rate & 0x8000 /* MCS15 */
		    &&
		    rf_type == RTL8712_RF_2T2R)
			max_rate = (bw_40MHz) ? ((short_GI) ? 300 : 270) :
			((short_GI) ? 144 : 130);
		else /* default MCS7 */
			max_rate = (bw_40MHz) ? ((short_GI) ? 150 : 135) :
			((short_GI) ? 72 : 65);
		max_rate *= 2; /* Mbps/2 */
	}
	wrqu->bitrate.value = max_rate * 500000;
	return 0;
}