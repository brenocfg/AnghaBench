#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char id; int /*<<< orphan*/  body; void* size; } ;
struct TYPE_7__ {unsigned char id; int /*<<< orphan*/  body; void* size; } ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * body; } ;
struct TYPE_5__ {int /*<<< orphan*/  body; void* size; } ;
struct local_ap {TYPE_4__ wpa_ie; TYPE_3__ rsn_ie; TYPE_2__ rate_set; TYPE_1__ ssid; int /*<<< orphan*/  channel; void* capability; int /*<<< orphan*/  noise; int /*<<< orphan*/  sq; int /*<<< orphan*/  rssi; int /*<<< orphan*/  bssid; } ;
struct ks_wlan_private {int /*<<< orphan*/  net_dev; } ;
struct ap_info {unsigned char* body; int /*<<< orphan*/  body_size; int /*<<< orphan*/  ch_info; int /*<<< orphan*/  capability; int /*<<< orphan*/  noise; int /*<<< orphan*/  sq; int /*<<< orphan*/  rssi; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_ID_WPA_WEP40 ; 
 int /*<<< orphan*/  IEEE80211_MAX_SSID_LEN ; 
 unsigned char RATE_SET_MAX_SIZE ; 
 int /*<<< orphan*/  RSN_IE_BODY_MAX ; 
#define  WLAN_EID_CF_PARAMS 139 
#define  WLAN_EID_COUNTRY 138 
#define  WLAN_EID_DS_PARAMS 137 
#define  WLAN_EID_ERP_INFO 136 
#define  WLAN_EID_EXT_SUPP_RATES 135 
#define  WLAN_EID_FH_PARAMS 134 
#define  WLAN_EID_IBSS_PARAMS 133 
#define  WLAN_EID_RSN 132 
#define  WLAN_EID_SSID 131 
#define  WLAN_EID_SUPP_RATES 130 
#define  WLAN_EID_TIM 129 
#define  WLAN_EID_VENDOR_SPECIFIC 128 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  memset (struct local_ap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned char) ; 
 void* read_ie (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int get_ap_information(struct ks_wlan_private *priv, struct ap_info *ap_info,
		       struct local_ap *ap)
{
	unsigned char *bp;
	int bsize, offset;

	memset(ap, 0, sizeof(struct local_ap));

	ether_addr_copy(ap->bssid, ap_info->bssid);
	ap->rssi = ap_info->rssi;
	ap->sq = ap_info->sq;
	ap->noise = ap_info->noise;
	ap->capability = le16_to_cpu(ap_info->capability);
	ap->channel = ap_info->ch_info;

	bp = ap_info->body;
	bsize = le16_to_cpu(ap_info->body_size);
	offset = 0;

	while (bsize > offset) {
		switch (*bp) { /* Information Element ID */
		case WLAN_EID_SSID:
			ap->ssid.size = read_ie(bp, IEEE80211_MAX_SSID_LEN,
						ap->ssid.body);
			break;
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_EXT_SUPP_RATES:
			if ((*(bp + 1) + ap->rate_set.size) <=
			    RATE_SET_MAX_SIZE) {
				memcpy(&ap->rate_set.body[ap->rate_set.size],
				       bp + 2, *(bp + 1));
				ap->rate_set.size += *(bp + 1);
			} else {
				memcpy(&ap->rate_set.body[ap->rate_set.size],
				       bp + 2,
				       RATE_SET_MAX_SIZE - ap->rate_set.size);
				ap->rate_set.size +=
				    (RATE_SET_MAX_SIZE - ap->rate_set.size);
			}
			break;
		case WLAN_EID_RSN:
			ap->rsn_ie.id = *bp;
			ap->rsn_ie.size = read_ie(bp, RSN_IE_BODY_MAX,
						  ap->rsn_ie.body);
			break;
		case WLAN_EID_VENDOR_SPECIFIC: /* WPA */
			/* WPA OUI check */
			if (memcmp(bp + 2, CIPHER_ID_WPA_WEP40, 4) == 0) {
				ap->wpa_ie.id = *bp;
				ap->wpa_ie.size = read_ie(bp, RSN_IE_BODY_MAX,
							  ap->wpa_ie.body);
			}
			break;
		case WLAN_EID_DS_PARAMS:
		case WLAN_EID_FH_PARAMS:
		case WLAN_EID_CF_PARAMS:
		case WLAN_EID_TIM:
		case WLAN_EID_IBSS_PARAMS:
		case WLAN_EID_COUNTRY:
		case WLAN_EID_ERP_INFO:
			break;
		default:
			netdev_err(priv->net_dev,
				   "unknown Element ID=%d\n", *bp);
			break;
		}

		offset += 2;	/* id & size field */
		offset += *(bp + 1);	/* +size offset */
		bp += (*(bp + 1) + 2);	/* pointer update */
	}

	return 0;
}