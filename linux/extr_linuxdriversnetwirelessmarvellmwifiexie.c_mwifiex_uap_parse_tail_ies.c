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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mwifiex_private {int gen_idx; } ;
struct mwifiex_ie {void* ie_length; void* mgmt_subtype_mask; void* ie_index; scalar_t__ ie_buffer; } ;
struct ieee_types_header {int element_id; int len; } ;
struct ieee80211_vendor_ie {int element_id; int len; } ;
struct cfg80211_beacon_data {int tail_len; int /*<<< orphan*/  const* tail; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MGMT_MASK_ASSOC_RESP ; 
 int MGMT_MASK_BEACON ; 
 int MGMT_MASK_PROBE_RESP ; 
 int MWIFIEX_AUTO_IDX_MASK ; 
#define  WLAN_EID_COUNTRY 138 
#define  WLAN_EID_ERP_INFO 137 
#define  WLAN_EID_EXT_SUPP_RATES 136 
#define  WLAN_EID_HT_CAPABILITY 135 
#define  WLAN_EID_HT_OPERATION 134 
#define  WLAN_EID_PWR_CONSTRAINT 133 
#define  WLAN_EID_SSID 132 
#define  WLAN_EID_SUPP_RATES 131 
#define  WLAN_EID_VENDOR_SPECIFIC 130 
#define  WLAN_EID_VHT_CAPABILITY 129 
#define  WLAN_EID_VHT_OPERATION 128 
 int /*<<< orphan*/  WLAN_OUI_MICROSOFT ; 
 int /*<<< orphan*/  WLAN_OUI_TYPE_MICROSOFT_WMM ; 
 int /*<<< orphan*/  WLAN_OUI_TYPE_MICROSOFT_WPA ; 
 scalar_t__ cfg80211_find_vendor_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_ie*) ; 
 struct mwifiex_ie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ieee_types_header*,int) ; 
 scalar_t__ mwifiex_update_uap_custom_ie (struct mwifiex_private*,struct mwifiex_ie*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_uap_parse_tail_ies(struct mwifiex_private *priv,
				      struct cfg80211_beacon_data *info)
{
	struct mwifiex_ie *gen_ie;
	struct ieee_types_header *hdr;
	struct ieee80211_vendor_ie *vendorhdr;
	u16 gen_idx = MWIFIEX_AUTO_IDX_MASK, ie_len = 0;
	int left_len, parsed_len = 0;

	if (!info->tail || !info->tail_len)
		return 0;

	gen_ie = kzalloc(sizeof(*gen_ie), GFP_KERNEL);
	if (!gen_ie)
		return -ENOMEM;

	left_len = info->tail_len;

	/* Many IEs are generated in FW by parsing bss configuration.
	 * Let's not add them here; else we may end up duplicating these IEs
	 */
	while (left_len > sizeof(struct ieee_types_header)) {
		hdr = (void *)(info->tail + parsed_len);
		switch (hdr->element_id) {
		case WLAN_EID_SSID:
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_COUNTRY:
		case WLAN_EID_PWR_CONSTRAINT:
		case WLAN_EID_ERP_INFO:
		case WLAN_EID_EXT_SUPP_RATES:
		case WLAN_EID_HT_CAPABILITY:
		case WLAN_EID_HT_OPERATION:
		case WLAN_EID_VHT_CAPABILITY:
		case WLAN_EID_VHT_OPERATION:
			break;
		case WLAN_EID_VENDOR_SPECIFIC:
			/* Skip only Microsoft WMM IE */
			if (cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WMM,
						    (const u8 *)hdr,
						    hdr->len + sizeof(struct ieee_types_header)))
				break;
		default:
			memcpy(gen_ie->ie_buffer + ie_len, hdr,
			       hdr->len + sizeof(struct ieee_types_header));
			ie_len += hdr->len + sizeof(struct ieee_types_header);
			break;
		}
		left_len -= hdr->len + sizeof(struct ieee_types_header);
		parsed_len += hdr->len + sizeof(struct ieee_types_header);
	}

	/* parse only WPA vendor IE from tail, WMM IE is configured by
	 * bss_config command
	 */
	vendorhdr = (void *)cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
						    WLAN_OUI_TYPE_MICROSOFT_WPA,
						    info->tail, info->tail_len);
	if (vendorhdr) {
		memcpy(gen_ie->ie_buffer + ie_len, vendorhdr,
		       vendorhdr->len + sizeof(struct ieee_types_header));
		ie_len += vendorhdr->len + sizeof(struct ieee_types_header);
	}

	if (!ie_len) {
		kfree(gen_ie);
		return 0;
	}

	gen_ie->ie_index = cpu_to_le16(gen_idx);
	gen_ie->mgmt_subtype_mask = cpu_to_le16(MGMT_MASK_BEACON |
						MGMT_MASK_PROBE_RESP |
						MGMT_MASK_ASSOC_RESP);
	gen_ie->ie_length = cpu_to_le16(ie_len);

	if (mwifiex_update_uap_custom_ie(priv, gen_ie, &gen_idx, NULL, NULL,
					 NULL, NULL)) {
		kfree(gen_ie);
		return -1;
	}

	priv->gen_idx = gen_idx;
	kfree(gen_ie);
	return 0;
}