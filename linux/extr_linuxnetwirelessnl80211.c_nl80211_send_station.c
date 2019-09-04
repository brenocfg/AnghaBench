#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  dtim_period; } ;
struct station_info {int filled; int assoc_req_ies_len; int /*<<< orphan*/  const* assoc_req_ies; struct cfg80211_tid_stats* pertid; int /*<<< orphan*/  avg_ack_signal; int /*<<< orphan*/  ack_signal; int /*<<< orphan*/  rx_beacon_signal_avg; scalar_t__ rx_beacon; scalar_t__ rx_dropped_misc; scalar_t__ t_offset; int /*<<< orphan*/  const sta_flags; TYPE_1__ bss_param; int /*<<< orphan*/  nonpeer_pm; int /*<<< orphan*/  peer_pm; int /*<<< orphan*/  local_pm; int /*<<< orphan*/  beacon_loss_count; int /*<<< orphan*/  expected_throughput; int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  tx_retries; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rxrate; int /*<<< orphan*/  txrate; int /*<<< orphan*/  chain_signal_avg; int /*<<< orphan*/  chains; int /*<<< orphan*/  chain_signal; int /*<<< orphan*/  signal_avg; int /*<<< orphan*/  signal; scalar_t__ rx_duration; int /*<<< orphan*/  plink_state; int /*<<< orphan*/  plid; int /*<<< orphan*/  llid; scalar_t__ tx_bytes; scalar_t__ rx_bytes; int /*<<< orphan*/  inactive_time; int /*<<< orphan*/  connected_time; int /*<<< orphan*/  generation; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nl80211_sta_flag_update {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct cfg80211_tid_stats {int filled; int /*<<< orphan*/  txq_stats; scalar_t__ tx_msdu_failed; scalar_t__ tx_msdu_retries; scalar_t__ tx_msdu; scalar_t__ rx_msdu; } ;
struct TYPE_4__ {int signal_type; } ;
struct cfg80211_registered_device {TYPE_2__ wiphy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_ULL (int) ; 
 int BSS_PARAM_FLAGS_CTS_PROT ; 
 int BSS_PARAM_FLAGS_SHORT_PREAMBLE ; 
 int BSS_PARAM_FLAGS_SHORT_SLOT_TIME ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  CFG80211_SIGNAL_TYPE_MBM 128 
 int EMSGSIZE ; 
 int ETH_ALEN ; 
 int IEEE80211_NUM_TIDS ; 
 int NL80211_ATTR_GENERATION ; 
 int NL80211_ATTR_IE ; 
 int NL80211_ATTR_IFINDEX ; 
 int NL80211_ATTR_MAC ; 
 int NL80211_ATTR_STA_INFO ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_DATA_ACK_SIGNAL_SUPPORT ; 
 int NL80211_STA_BSS_PARAM_BEACON_INTERVAL ; 
 int /*<<< orphan*/  NL80211_STA_BSS_PARAM_CTS_PROT ; 
 int NL80211_STA_BSS_PARAM_DTIM_PERIOD ; 
 int /*<<< orphan*/  NL80211_STA_BSS_PARAM_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME ; 
 int NL80211_STA_INFO_ACK_SIGNAL ; 
 int NL80211_STA_INFO_BEACON_LOSS ; 
 int NL80211_STA_INFO_BEACON_RX ; 
 int NL80211_STA_INFO_BEACON_SIGNAL_AVG ; 
 int NL80211_STA_INFO_BSS_PARAM ; 
 int NL80211_STA_INFO_CHAIN_SIGNAL ; 
 int NL80211_STA_INFO_CHAIN_SIGNAL_AVG ; 
 int NL80211_STA_INFO_CONNECTED_TIME ; 
 int NL80211_STA_INFO_DATA_ACK_SIGNAL_AVG ; 
 int NL80211_STA_INFO_EXPECTED_THROUGHPUT ; 
 int NL80211_STA_INFO_INACTIVE_TIME ; 
 int NL80211_STA_INFO_LLID ; 
 int NL80211_STA_INFO_LOCAL_PM ; 
 int NL80211_STA_INFO_NONPEER_PM ; 
 int /*<<< orphan*/  NL80211_STA_INFO_PAD ; 
 int NL80211_STA_INFO_PEER_PM ; 
 int NL80211_STA_INFO_PLID ; 
 int NL80211_STA_INFO_PLINK_STATE ; 
 int NL80211_STA_INFO_RX_BITRATE ; 
 int NL80211_STA_INFO_RX_BYTES ; 
 int NL80211_STA_INFO_RX_BYTES64 ; 
 int NL80211_STA_INFO_RX_DROP_MISC ; 
 int NL80211_STA_INFO_RX_DURATION ; 
 int NL80211_STA_INFO_RX_PACKETS ; 
 int NL80211_STA_INFO_SIGNAL ; 
 int NL80211_STA_INFO_SIGNAL_AVG ; 
 int NL80211_STA_INFO_STA_FLAGS ; 
 int NL80211_STA_INFO_TID_STATS ; 
 int NL80211_STA_INFO_TX_BITRATE ; 
 int NL80211_STA_INFO_TX_BYTES ; 
 int NL80211_STA_INFO_TX_BYTES64 ; 
 int NL80211_STA_INFO_TX_FAILED ; 
 int NL80211_STA_INFO_TX_PACKETS ; 
 int NL80211_STA_INFO_TX_RETRIES ; 
 int NL80211_STA_INFO_T_OFFSET ; 
 int /*<<< orphan*/  NL80211_TID_STATS_PAD ; 
 int NL80211_TID_STATS_RX_MSDU ; 
 int NL80211_TID_STATS_TXQ_STATS ; 
 int NL80211_TID_STATS_TX_MSDU ; 
 int NL80211_TID_STATS_TX_MSDU_FAILED ; 
 int NL80211_TID_STATS_TX_MSDU_RETRIES ; 
 int /*<<< orphan*/  cfg80211_sinfo_release_content (struct station_info*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  nl80211_put_signal (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_put_sta_rate (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nl80211_put_txq_stats (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 scalar_t__ nla_put (struct sk_buff*,int,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ wiphy_ext_feature_isset (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_send_station(struct sk_buff *msg, u32 cmd, u32 portid,
				u32 seq, int flags,
				struct cfg80211_registered_device *rdev,
				struct net_device *dev,
				const u8 *mac_addr, struct station_info *sinfo)
{
	void *hdr;
	struct nlattr *sinfoattr, *bss_param;

	hdr = nl80211hdr_put(msg, portid, seq, flags, cmd);
	if (!hdr)
		return -1;

	if (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac_addr) ||
	    nla_put_u32(msg, NL80211_ATTR_GENERATION, sinfo->generation))
		goto nla_put_failure;

	sinfoattr = nla_nest_start(msg, NL80211_ATTR_STA_INFO);
	if (!sinfoattr)
		goto nla_put_failure;

#define PUT_SINFO(attr, memb, type) do {				\
	BUILD_BUG_ON(sizeof(type) == sizeof(u64));			\
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_ ## attr) &&	\
	    nla_put_ ## type(msg, NL80211_STA_INFO_ ## attr,		\
			     sinfo->memb))				\
		goto nla_put_failure;					\
	} while (0)
#define PUT_SINFO_U64(attr, memb) do {					\
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_ ## attr) &&	\
	    nla_put_u64_64bit(msg, NL80211_STA_INFO_ ## attr,		\
			      sinfo->memb, NL80211_STA_INFO_PAD))	\
		goto nla_put_failure;					\
	} while (0)

	PUT_SINFO(CONNECTED_TIME, connected_time, u32);
	PUT_SINFO(INACTIVE_TIME, inactive_time, u32);

	if (sinfo->filled & (BIT_ULL(NL80211_STA_INFO_RX_BYTES) |
			     BIT_ULL(NL80211_STA_INFO_RX_BYTES64)) &&
	    nla_put_u32(msg, NL80211_STA_INFO_RX_BYTES,
			(u32)sinfo->rx_bytes))
		goto nla_put_failure;

	if (sinfo->filled & (BIT_ULL(NL80211_STA_INFO_TX_BYTES) |
			     BIT_ULL(NL80211_STA_INFO_TX_BYTES64)) &&
	    nla_put_u32(msg, NL80211_STA_INFO_TX_BYTES,
			(u32)sinfo->tx_bytes))
		goto nla_put_failure;

	PUT_SINFO_U64(RX_BYTES64, rx_bytes);
	PUT_SINFO_U64(TX_BYTES64, tx_bytes);
	PUT_SINFO(LLID, llid, u16);
	PUT_SINFO(PLID, plid, u16);
	PUT_SINFO(PLINK_STATE, plink_state, u8);
	PUT_SINFO_U64(RX_DURATION, rx_duration);

	switch (rdev->wiphy.signal_type) {
	case CFG80211_SIGNAL_TYPE_MBM:
		PUT_SINFO(SIGNAL, signal, u8);
		PUT_SINFO(SIGNAL_AVG, signal_avg, u8);
		break;
	default:
		break;
	}
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL)) {
		if (!nl80211_put_signal(msg, sinfo->chains,
					sinfo->chain_signal,
					NL80211_STA_INFO_CHAIN_SIGNAL))
			goto nla_put_failure;
	}
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL_AVG)) {
		if (!nl80211_put_signal(msg, sinfo->chains,
					sinfo->chain_signal_avg,
					NL80211_STA_INFO_CHAIN_SIGNAL_AVG))
			goto nla_put_failure;
	}
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE)) {
		if (!nl80211_put_sta_rate(msg, &sinfo->txrate,
					  NL80211_STA_INFO_TX_BITRATE))
			goto nla_put_failure;
	}
	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_RX_BITRATE)) {
		if (!nl80211_put_sta_rate(msg, &sinfo->rxrate,
					  NL80211_STA_INFO_RX_BITRATE))
			goto nla_put_failure;
	}

	PUT_SINFO(RX_PACKETS, rx_packets, u32);
	PUT_SINFO(TX_PACKETS, tx_packets, u32);
	PUT_SINFO(TX_RETRIES, tx_retries, u32);
	PUT_SINFO(TX_FAILED, tx_failed, u32);
	PUT_SINFO(EXPECTED_THROUGHPUT, expected_throughput, u32);
	PUT_SINFO(BEACON_LOSS, beacon_loss_count, u32);
	PUT_SINFO(LOCAL_PM, local_pm, u32);
	PUT_SINFO(PEER_PM, peer_pm, u32);
	PUT_SINFO(NONPEER_PM, nonpeer_pm, u32);

	if (sinfo->filled & BIT_ULL(NL80211_STA_INFO_BSS_PARAM)) {
		bss_param = nla_nest_start(msg, NL80211_STA_INFO_BSS_PARAM);
		if (!bss_param)
			goto nla_put_failure;

		if (((sinfo->bss_param.flags & BSS_PARAM_FLAGS_CTS_PROT) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_CTS_PROT)) ||
		    ((sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_PREAMBLE) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_SHORT_PREAMBLE)) ||
		    ((sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_SLOT_TIME) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME)) ||
		    nla_put_u8(msg, NL80211_STA_BSS_PARAM_DTIM_PERIOD,
			       sinfo->bss_param.dtim_period) ||
		    nla_put_u16(msg, NL80211_STA_BSS_PARAM_BEACON_INTERVAL,
				sinfo->bss_param.beacon_interval))
			goto nla_put_failure;

		nla_nest_end(msg, bss_param);
	}
	if ((sinfo->filled & BIT_ULL(NL80211_STA_INFO_STA_FLAGS)) &&
	    nla_put(msg, NL80211_STA_INFO_STA_FLAGS,
		    sizeof(struct nl80211_sta_flag_update),
		    &sinfo->sta_flags))
		goto nla_put_failure;

	PUT_SINFO_U64(T_OFFSET, t_offset);
	PUT_SINFO_U64(RX_DROP_MISC, rx_dropped_misc);
	PUT_SINFO_U64(BEACON_RX, rx_beacon);
	PUT_SINFO(BEACON_SIGNAL_AVG, rx_beacon_signal_avg, u8);
	PUT_SINFO(ACK_SIGNAL, ack_signal, u8);
	if (wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_DATA_ACK_SIGNAL_SUPPORT))
		PUT_SINFO(DATA_ACK_SIGNAL_AVG, avg_ack_signal, s8);

#undef PUT_SINFO
#undef PUT_SINFO_U64

	if (sinfo->pertid) {
		struct nlattr *tidsattr;
		int tid;

		tidsattr = nla_nest_start(msg, NL80211_STA_INFO_TID_STATS);
		if (!tidsattr)
			goto nla_put_failure;

		for (tid = 0; tid < IEEE80211_NUM_TIDS + 1; tid++) {
			struct cfg80211_tid_stats *tidstats;
			struct nlattr *tidattr;

			tidstats = &sinfo->pertid[tid];

			if (!tidstats->filled)
				continue;

			tidattr = nla_nest_start(msg, tid + 1);
			if (!tidattr)
				goto nla_put_failure;

#define PUT_TIDVAL_U64(attr, memb) do {					\
	if (tidstats->filled & BIT(NL80211_TID_STATS_ ## attr) &&	\
	    nla_put_u64_64bit(msg, NL80211_TID_STATS_ ## attr,		\
			      tidstats->memb, NL80211_TID_STATS_PAD))	\
		goto nla_put_failure;					\
	} while (0)

			PUT_TIDVAL_U64(RX_MSDU, rx_msdu);
			PUT_TIDVAL_U64(TX_MSDU, tx_msdu);
			PUT_TIDVAL_U64(TX_MSDU_RETRIES, tx_msdu_retries);
			PUT_TIDVAL_U64(TX_MSDU_FAILED, tx_msdu_failed);

#undef PUT_TIDVAL_U64
			if ((tidstats->filled &
			     BIT(NL80211_TID_STATS_TXQ_STATS)) &&
			    !nl80211_put_txq_stats(msg, &tidstats->txq_stats,
						   NL80211_TID_STATS_TXQ_STATS))
				goto nla_put_failure;

			nla_nest_end(msg, tidattr);
		}

		nla_nest_end(msg, tidsattr);
	}

	nla_nest_end(msg, sinfoattr);

	if (sinfo->assoc_req_ies_len &&
	    nla_put(msg, NL80211_ATTR_IE, sinfo->assoc_req_ies_len,
		    sinfo->assoc_req_ies))
		goto nla_put_failure;

	cfg80211_sinfo_release_content(sinfo);
	genlmsg_end(msg, hdr);
	return 0;

 nla_put_failure:
	cfg80211_sinfo_release_content(sinfo);
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}