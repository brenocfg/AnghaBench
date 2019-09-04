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
struct sk_buff {int dummy; } ;
struct mwifiex_private {int dummy; } ;
struct ieee80211_wmm_param_ie {int len; int* oui; int oui_type; int oui_subtype; int version; int /*<<< orphan*/ * ac; scalar_t__ qos_info; int /*<<< orphan*/  element_id; } ;
typedef  int /*<<< orphan*/  ac_vo ;
typedef  int /*<<< orphan*/  ac_vi ;
typedef  int /*<<< orphan*/  ac_bk ;
typedef  int /*<<< orphan*/  ac_be ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 struct ieee80211_wmm_param_ie* skb_put_zero (struct sk_buff*,int) ; 

__attribute__((used)) static void
mwifiex_tdls_add_wmm_param_ie(struct mwifiex_private *priv, struct sk_buff *skb)
{
	struct ieee80211_wmm_param_ie *wmm;
	u8 ac_vi[] = {0x42, 0x43, 0x5e, 0x00};
	u8 ac_vo[] = {0x62, 0x32, 0x2f, 0x00};
	u8 ac_be[] = {0x03, 0xa4, 0x00, 0x00};
	u8 ac_bk[] = {0x27, 0xa4, 0x00, 0x00};

	wmm = skb_put_zero(skb, sizeof(*wmm));

	wmm->element_id = WLAN_EID_VENDOR_SPECIFIC;
	wmm->len = sizeof(*wmm) - 2;
	wmm->oui[0] = 0x00; /* Microsoft OUI 00:50:F2 */
	wmm->oui[1] = 0x50;
	wmm->oui[2] = 0xf2;
	wmm->oui_type = 2; /* WME */
	wmm->oui_subtype = 1; /* WME param */
	wmm->version = 1; /* WME ver */
	wmm->qos_info = 0; /* U-APSD not in use */

	/* use default WMM AC parameters for TDLS link*/
	memcpy(&wmm->ac[0], ac_be, sizeof(ac_be));
	memcpy(&wmm->ac[1], ac_bk, sizeof(ac_bk));
	memcpy(&wmm->ac[2], ac_vi, sizeof(ac_vi));
	memcpy(&wmm->ac[3], ac_vo, sizeof(ac_vo));
}