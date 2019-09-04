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
typedef  int u8 ;
typedef  void* u16 ;
struct wiphy {int dummy; } ;
struct lbs_private {TYPE_1__* wdev; } ;
struct ieee80211_channel {int flags; } ;
struct cmd_header {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_scan_rsp {int const bssdescriptsize; int nr_sets; int* bssdesc_and_tlvbuffer; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_2__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 int EILSEQ ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  LBS_DEB_SCAN ; 
 int LBS_SCAN_RSSI_TO_MBM (int) ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int TLV_TYPE_TSFTIMESTAMP ; 
 int WLAN_EID_DS_PARAMS ; 
 int WLAN_EID_SSID ; 
 struct cfg80211_bss* cfg80211_inform_bss (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ,void*,void*,int const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 void* get_unaligned_le16 (int const*) ; 
 int /*<<< orphan*/  get_unaligned_le64 (int const*) ; 
 int ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  lbs_deb_scan (char*,...) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_ret_scan(struct lbs_private *priv, unsigned long dummy,
	struct cmd_header *resp)
{
	struct cfg80211_bss *bss;
	struct cmd_ds_802_11_scan_rsp *scanresp = (void *)resp;
	int bsssize;
	const u8 *pos;
	const u8 *tsfdesc;
	int tsfsize;
	int i;
	int ret = -EILSEQ;

	bsssize = get_unaligned_le16(&scanresp->bssdescriptsize);

	lbs_deb_scan("scan response: %d BSSs (%d bytes); resp size %d bytes\n",
			scanresp->nr_sets, bsssize, le16_to_cpu(resp->size));

	if (scanresp->nr_sets == 0) {
		ret = 0;
		goto done;
	}

	/*
	 * The general layout of the scan response is described in chapter
	 * 5.7.1. Basically we have a common part, then any number of BSS
	 * descriptor sections. Finally we have section with the same number
	 * of TSFs.
	 *
	 * cmd_ds_802_11_scan_rsp
	 *   cmd_header
	 *   pos_size
	 *   nr_sets
	 *   bssdesc 1
	 *     bssid
	 *     rssi
	 *     timestamp
	 *     intvl
	 *     capa
	 *     IEs
	 *   bssdesc 2
	 *   bssdesc n
	 *   MrvlIEtypes_TsfFimestamp_t
	 *     TSF for BSS 1
	 *     TSF for BSS 2
	 *     TSF for BSS n
	 */

	pos = scanresp->bssdesc_and_tlvbuffer;

	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_RSP", scanresp->bssdesc_and_tlvbuffer,
			scanresp->bssdescriptsize);

	tsfdesc = pos + bsssize;
	tsfsize = 4 + 8 * scanresp->nr_sets;
	lbs_deb_hex(LBS_DEB_SCAN, "SCAN_TSF", (u8 *) tsfdesc, tsfsize);

	/* Validity check: we expect a Marvell-Local TLV */
	i = get_unaligned_le16(tsfdesc);
	tsfdesc += 2;
	if (i != TLV_TYPE_TSFTIMESTAMP) {
		lbs_deb_scan("scan response: invalid TSF Timestamp %d\n", i);
		goto done;
	}

	/*
	 * Validity check: the TLV holds TSF values with 8 bytes each, so
	 * the size in the TLV must match the nr_sets value
	 */
	i = get_unaligned_le16(tsfdesc);
	tsfdesc += 2;
	if (i / 8 != scanresp->nr_sets) {
		lbs_deb_scan("scan response: invalid number of TSF timestamp "
			     "sets (expected %d got %d)\n", scanresp->nr_sets,
			     i / 8);
		goto done;
	}

	for (i = 0; i < scanresp->nr_sets; i++) {
		const u8 *bssid;
		const u8 *ie;
		int left;
		int ielen;
		int rssi;
		u16 intvl;
		u16 capa;
		int chan_no = -1;
		const u8 *ssid = NULL;
		u8 ssid_len = 0;

		int len = get_unaligned_le16(pos);
		pos += 2;

		/* BSSID */
		bssid = pos;
		pos += ETH_ALEN;
		/* RSSI */
		rssi = *pos++;
		/* Packet time stamp */
		pos += 8;
		/* Beacon interval */
		intvl = get_unaligned_le16(pos);
		pos += 2;
		/* Capabilities */
		capa = get_unaligned_le16(pos);
		pos += 2;

		/* To find out the channel, we must parse the IEs */
		ie = pos;
		/*
		 * 6+1+8+2+2: size of BSSID, RSSI, time stamp, beacon
		 * interval, capabilities
		 */
		ielen = left = len - (6 + 1 + 8 + 2 + 2);
		while (left >= 2) {
			u8 id, elen;
			id = *pos++;
			elen = *pos++;
			left -= 2;
			if (elen > left) {
				lbs_deb_scan("scan response: invalid IE fmt\n");
				goto done;
			}

			if (id == WLAN_EID_DS_PARAMS)
				chan_no = *pos;
			if (id == WLAN_EID_SSID) {
				ssid = pos;
				ssid_len = elen;
			}
			left -= elen;
			pos += elen;
		}

		/* No channel, no luck */
		if (chan_no != -1) {
			struct wiphy *wiphy = priv->wdev->wiphy;
			int freq = ieee80211_channel_to_frequency(chan_no,
							NL80211_BAND_2GHZ);
			struct ieee80211_channel *channel =
				ieee80211_get_channel(wiphy, freq);

			lbs_deb_scan("scan: %pM, capa %04x, chan %2d, %*pE, %d dBm\n",
				     bssid, capa, chan_no, ssid_len, ssid,
				     LBS_SCAN_RSSI_TO_MBM(rssi)/100);

			if (channel &&
			    !(channel->flags & IEEE80211_CHAN_DISABLED)) {
				bss = cfg80211_inform_bss(wiphy, channel,
					CFG80211_BSS_FTYPE_UNKNOWN,
					bssid, get_unaligned_le64(tsfdesc),
					capa, intvl, ie, ielen,
					LBS_SCAN_RSSI_TO_MBM(rssi),
					GFP_KERNEL);
				cfg80211_put_bss(wiphy, bss);
			}
		} else
			lbs_deb_scan("scan response: missing BSS channel IE\n");

		tsfdesc += 8;
	}
	ret = 0;

 done:
	return ret;
}