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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct qos_priv {int qos_option; } ;
struct ht_priv {int ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; struct qos_priv qospriv; } ;
struct ieee80211_ht_cap {int ampdu_params_info; int /*<<< orphan*/  cap_info; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_AMPDU_DENSITY ; 
 int IEEE80211_HT_CAP_AMPDU_FACTOR ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 int /*<<< orphan*/  _VENDOR_SPECIFIC_IE_ ; 
 int _WMM_IE_Length_ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_ht_cap*,int /*<<< orphan*/ ,int) ; 
 unsigned char* r8712_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  r8712_set_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,scalar_t__*) ; 

unsigned int r8712_restructure_ht_ie(struct _adapter *padapter, u8 *in_ie,
				     u8 *out_ie, uint in_len, uint *pout_len)
{
	u32 ielen, out_len;
	unsigned char *p;
	struct ieee80211_ht_cap ht_capie;
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct qos_priv *pqospriv = &pmlmepriv->qospriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;

	phtpriv->ht_option = 0;
	p = r8712_get_ie(in_ie + 12, _HT_CAPABILITY_IE_, &ielen, in_len - 12);
	if (p && (ielen > 0)) {
		if (pqospriv->qos_option == 0) {
			out_len = *pout_len;
			r8712_set_ie(out_ie + out_len, _VENDOR_SPECIFIC_IE_,
				     _WMM_IE_Length_, WMM_IE, pout_len);
			pqospriv->qos_option = 1;
		}
		out_len = *pout_len;
		memset(&ht_capie, 0, sizeof(struct ieee80211_ht_cap));
		ht_capie.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH |
				    IEEE80211_HT_CAP_SGI_20 |
				    IEEE80211_HT_CAP_SGI_40 |
				    IEEE80211_HT_CAP_TX_STBC |
				    IEEE80211_HT_CAP_MAX_AMSDU |
				    IEEE80211_HT_CAP_DSSSCCK40);
		ht_capie.ampdu_params_info = (IEEE80211_HT_CAP_AMPDU_FACTOR &
				0x03) | (IEEE80211_HT_CAP_AMPDU_DENSITY & 0x00);
		r8712_set_ie(out_ie + out_len, _HT_CAPABILITY_IE_,
			     sizeof(struct ieee80211_ht_cap),
			     (unsigned char *)&ht_capie, pout_len);
		phtpriv->ht_option = 1;
	}
	return phtpriv->ht_option;
}