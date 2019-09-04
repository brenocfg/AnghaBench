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
typedef  int u16 ;
struct rxpd {int /*<<< orphan*/  nf; int /*<<< orphan*/  snr; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct ieee80211_hdr {int* addr2; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int IEEE80211_FCTL_STYPE ; 
#define  IEEE80211_STYPE_ACTION 130 
 int /*<<< orphan*/  INFO ; 
#define  WLAN_CATEGORY_BACK 129 
#define  WLAN_CATEGORY_PUBLIC 128 
 int WLAN_PUB_ACTION_TDLS_DISCOVER_RES ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_auto_tdls_update_peer_signal (struct mwifiex_private*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
mwifiex_parse_mgmt_packet(struct mwifiex_private *priv, u8 *payload, u16 len,
			  struct rxpd *rx_pd)
{
	u16 stype;
	u8 category, action_code, *addr2;
	struct ieee80211_hdr *ieee_hdr = (void *)payload;

	stype = (le16_to_cpu(ieee_hdr->frame_control) & IEEE80211_FCTL_STYPE);

	switch (stype) {
	case IEEE80211_STYPE_ACTION:
		category = *(payload + sizeof(struct ieee80211_hdr));
		switch (category) {
		case WLAN_CATEGORY_PUBLIC:
			action_code = *(payload + sizeof(struct ieee80211_hdr)
					+ 1);
			if (action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) {
				addr2 = ieee_hdr->addr2;
				mwifiex_dbg(priv->adapter, INFO,
					    "TDLS discovery response %pM nf=%d, snr=%d\n",
					    addr2, rx_pd->nf, rx_pd->snr);
				mwifiex_auto_tdls_update_peer_signal(priv,
								     addr2,
								     rx_pd->snr,
								     rx_pd->nf);
			}
			break;
		case WLAN_CATEGORY_BACK:
			/*we dont indicate BACK action frames to cfg80211*/
			mwifiex_dbg(priv->adapter, INFO,
				    "drop BACK action frames");
			return -1;
		default:
			mwifiex_dbg(priv->adapter, INFO,
				    "unknown public action frame category %d\n",
				    category);
		}
		break;
	default:
		mwifiex_dbg(priv->adapter, INFO,
		    "unknown mgmt frame subtype %#x\n", stype);
		return 0;
	}

	return 0;
}