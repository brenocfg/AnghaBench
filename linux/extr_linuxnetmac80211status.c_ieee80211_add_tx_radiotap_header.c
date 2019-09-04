#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_4__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_3__ status; } ;
struct ieee80211_supported_band {TYPE_1__* bitrates; } ;
struct ieee80211_radiotap_header {int /*<<< orphan*/  it_present; int /*<<< orphan*/  it_len; } ;
struct TYPE_7__ {int radiotap_vht_details; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
struct TYPE_9__ {size_t idx; int flags; } ;
struct TYPE_6__ {int bitrate; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 unsigned char DIV_ROUND_UP (int,int) ; 
 int IEEE80211_RADIOTAP_DATA_RETRIES ; 
 int IEEE80211_RADIOTAP_F_TX_CTS ; 
 int IEEE80211_RADIOTAP_F_TX_FAIL ; 
 int IEEE80211_RADIOTAP_F_TX_RTS ; 
 int IEEE80211_RADIOTAP_MCS ; 
 unsigned char IEEE80211_RADIOTAP_MCS_BW_40 ; 
 unsigned char IEEE80211_RADIOTAP_MCS_FMT_GF ; 
 unsigned char IEEE80211_RADIOTAP_MCS_HAVE_BW ; 
 unsigned char IEEE80211_RADIOTAP_MCS_HAVE_GI ; 
 unsigned char IEEE80211_RADIOTAP_MCS_HAVE_MCS ; 
 unsigned char IEEE80211_RADIOTAP_MCS_SGI ; 
 int IEEE80211_RADIOTAP_RATE ; 
 int IEEE80211_RADIOTAP_TX_FLAGS ; 
 int IEEE80211_RADIOTAP_VHT ; 
 unsigned char IEEE80211_RADIOTAP_VHT_FLAG_SGI ; 
 int IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH ; 
 int IEEE80211_RADIOTAP_VHT_KNOWN_GI ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ieee80211_rate_get_vht_mcs (TYPE_4__*) ; 
 int ieee80211_rate_get_vht_nss (TYPE_4__*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_radiotap_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,unsigned char*) ; 
 struct ieee80211_radiotap_header* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void
ieee80211_add_tx_radiotap_header(struct ieee80211_local *local,
				 struct ieee80211_supported_band *sband,
				 struct sk_buff *skb, int retry_count,
				 int rtap_len, int shift)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_radiotap_header *rthdr;
	unsigned char *pos;
	u16 txflags;

	rthdr = skb_push(skb, rtap_len);

	memset(rthdr, 0, rtap_len);
	rthdr->it_len = cpu_to_le16(rtap_len);
	rthdr->it_present =
		cpu_to_le32((1 << IEEE80211_RADIOTAP_TX_FLAGS) |
			    (1 << IEEE80211_RADIOTAP_DATA_RETRIES));
	pos = (unsigned char *)(rthdr + 1);

	/*
	 * XXX: Once radiotap gets the bitmap reset thing the vendor
	 *	extensions proposal contains, we can actually report
	 *	the whole set of tries we did.
	 */

	/* IEEE80211_RADIOTAP_RATE */
	if (info->status.rates[0].idx >= 0 &&
	    !(info->status.rates[0].flags & (IEEE80211_TX_RC_MCS |
					     IEEE80211_TX_RC_VHT_MCS))) {
		u16 rate;

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_RATE);
		rate = sband->bitrates[info->status.rates[0].idx].bitrate;
		*pos = DIV_ROUND_UP(rate, 5 * (1 << shift));
		/* padding for tx flags */
		pos += 2;
	}

	/* IEEE80211_RADIOTAP_TX_FLAGS */
	txflags = 0;
	if (!(info->flags & IEEE80211_TX_STAT_ACK) &&
	    !is_multicast_ether_addr(hdr->addr1))
		txflags |= IEEE80211_RADIOTAP_F_TX_FAIL;

	if (info->status.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		txflags |= IEEE80211_RADIOTAP_F_TX_CTS;
	if (info->status.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
		txflags |= IEEE80211_RADIOTAP_F_TX_RTS;

	put_unaligned_le16(txflags, pos);
	pos += 2;

	/* IEEE80211_RADIOTAP_DATA_RETRIES */
	/* for now report the total retry_count */
	*pos = retry_count;
	pos++;

	if (info->status.rates[0].idx < 0)
		return;

	/* IEEE80211_RADIOTAP_MCS
	 * IEEE80211_RADIOTAP_VHT */
	if (info->status.rates[0].flags & IEEE80211_TX_RC_MCS) {
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_MCS);
		pos[0] = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
			 IEEE80211_RADIOTAP_MCS_HAVE_GI |
			 IEEE80211_RADIOTAP_MCS_HAVE_BW;
		if (info->status.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			pos[1] |= IEEE80211_RADIOTAP_MCS_SGI;
		if (info->status.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			pos[1] |= IEEE80211_RADIOTAP_MCS_BW_40;
		if (info->status.rates[0].flags & IEEE80211_TX_RC_GREEN_FIELD)
			pos[1] |= IEEE80211_RADIOTAP_MCS_FMT_GF;
		pos[2] = info->status.rates[0].idx;
		pos += 3;
	} else if (info->status.rates[0].flags & IEEE80211_TX_RC_VHT_MCS) {
		u16 known = local->hw.radiotap_vht_details &
			(IEEE80211_RADIOTAP_VHT_KNOWN_GI |
			 IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH);

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_VHT);

		/* required alignment from rthdr */
		pos = (u8 *)rthdr + ALIGN(pos - (u8 *)rthdr, 2);

		/* u16 known - IEEE80211_RADIOTAP_VHT_KNOWN_* */
		put_unaligned_le16(known, pos);
		pos += 2;

		/* u8 flags - IEEE80211_RADIOTAP_VHT_FLAG_* */
		if (info->status.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_SGI;
		pos++;

		/* u8 bandwidth */
		if (info->status.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			*pos = 1;
		else if (info->status.rates[0].flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			*pos = 4;
		else if (info->status.rates[0].flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
			*pos = 11;
		else /* IEEE80211_TX_RC_{20_MHZ_WIDTH,FIXME:DUP_DATA} */
			*pos = 0;
		pos++;

		/* u8 mcs_nss[4] */
		*pos = (ieee80211_rate_get_vht_mcs(&info->status.rates[0]) << 4) |
			ieee80211_rate_get_vht_nss(&info->status.rates[0]);
		pos += 4;

		/* u8 coding */
		pos++;
		/* u8 group_id */
		pos++;
		/* u16 partial_aid */
		pos += 2;
	}
}