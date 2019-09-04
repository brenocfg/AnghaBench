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
struct stmmac_extra_stats {int /*<<< orphan*/  l3_l4_filter_no_match; int /*<<< orphan*/  l4_filter_match; int /*<<< orphan*/  l3_filter_match; int /*<<< orphan*/  da_rx_filter_fail; int /*<<< orphan*/  sa_rx_filter_fail; int /*<<< orphan*/  timestamp_dropped; int /*<<< orphan*/  ptp_ver; int /*<<< orphan*/  ptp_frame_type; int /*<<< orphan*/  ptp_rx_msg_pkt_reserved_type; int /*<<< orphan*/  ptp_rx_msg_type_management; int /*<<< orphan*/  ptp_rx_msg_type_announce; int /*<<< orphan*/  ptp_rx_msg_type_pdelay_follow_up; int /*<<< orphan*/  ptp_rx_msg_type_pdelay_resp; int /*<<< orphan*/  ptp_rx_msg_type_pdelay_req; int /*<<< orphan*/  ptp_rx_msg_type_delay_resp; int /*<<< orphan*/  ptp_rx_msg_type_delay_req; int /*<<< orphan*/  ptp_rx_msg_type_follow_up; int /*<<< orphan*/  ptp_rx_msg_type_sync; int /*<<< orphan*/  no_ptp_rx_msg_type_ext; int /*<<< orphan*/  ipv6_pkt_rcvd; int /*<<< orphan*/  ipv4_pkt_rcvd; int /*<<< orphan*/  ip_csum_bypassed; int /*<<< orphan*/  ip_hdr_err; int /*<<< orphan*/  dribbling_bit; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_mii; int /*<<< orphan*/  rx_watchdog; int /*<<< orphan*/  rx_gmac_overflow; } ;
struct net_device_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; int /*<<< orphan*/  des1; } ;

/* Variables and functions */
 unsigned int ERDES4_MSG_TYPE_MASK ; 
 unsigned int RDES1_IPV4_HEADER ; 
 unsigned int RDES1_IPV6_HEADER ; 
 unsigned int RDES1_IP_CSUM_BYPASSED ; 
 unsigned int RDES1_IP_HDR_ERROR ; 
 unsigned int RDES1_PTP_PACKET_TYPE ; 
 unsigned int RDES1_PTP_VER ; 
 unsigned int RDES1_TIMESTAMP_DROPPED ; 
 unsigned int RDES2_DA_FILTER_FAIL ; 
 unsigned int RDES2_L3_FILTER_MATCH ; 
 unsigned int RDES2_L3_L4_FILT_NB_MATCH_MASK ; 
 unsigned int RDES2_L3_L4_FILT_NB_MATCH_SHIFT ; 
 unsigned int RDES2_L4_FILTER_MATCH ; 
 unsigned int RDES2_SA_FILTER_FAIL ; 
 unsigned int RDES3_CRC_ERROR ; 
 unsigned int RDES3_DRIBBLE_ERROR ; 
 unsigned int RDES3_ERROR_SUMMARY ; 
 unsigned int RDES3_GIANT_PACKET ; 
 unsigned int RDES3_LAST_DESCRIPTOR ; 
 unsigned int RDES3_OVERFLOW_ERROR ; 
 unsigned int RDES3_OWN ; 
 unsigned int RDES3_RECEIVE_ERROR ; 
 unsigned int RDES3_RECEIVE_WATCHDOG ; 
 int RDES_EXT_DELAY_REQ ; 
 int RDES_EXT_DELAY_RESP ; 
 int RDES_EXT_FOLLOW_UP ; 
 int RDES_EXT_NO_PTP ; 
 int RDES_EXT_PDELAY_FOLLOW_UP ; 
 int RDES_EXT_PDELAY_REQ ; 
 int RDES_EXT_PDELAY_RESP ; 
 int RDES_EXT_SYNC ; 
 int RDES_PTP_ANNOUNCE ; 
 int RDES_PTP_MANAGEMENT ; 
 int RDES_PTP_PKT_RESERVED_TYPE ; 
 int discard_frame ; 
 int dma_own ; 
 int good_frame ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int dwmac4_wrback_get_rx_status(void *data, struct stmmac_extra_stats *x,
				       struct dma_desc *p)
{
	struct net_device_stats *stats = (struct net_device_stats *)data;
	unsigned int rdes1 = le32_to_cpu(p->des1);
	unsigned int rdes2 = le32_to_cpu(p->des2);
	unsigned int rdes3 = le32_to_cpu(p->des3);
	int message_type;
	int ret = good_frame;

	if (unlikely(rdes3 & RDES3_OWN))
		return dma_own;

	/* Verify rx error by looking at the last segment. */
	if (likely(!(rdes3 & RDES3_LAST_DESCRIPTOR)))
		return discard_frame;

	if (unlikely(rdes3 & RDES3_ERROR_SUMMARY)) {
		if (unlikely(rdes3 & RDES3_GIANT_PACKET))
			stats->rx_length_errors++;
		if (unlikely(rdes3 & RDES3_OVERFLOW_ERROR))
			x->rx_gmac_overflow++;

		if (unlikely(rdes3 & RDES3_RECEIVE_WATCHDOG))
			x->rx_watchdog++;

		if (unlikely(rdes3 & RDES3_RECEIVE_ERROR))
			x->rx_mii++;

		if (unlikely(rdes3 & RDES3_CRC_ERROR)) {
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		}

		if (unlikely(rdes3 & RDES3_DRIBBLE_ERROR))
			x->dribbling_bit++;

		ret = discard_frame;
	}

	message_type = (rdes1 & ERDES4_MSG_TYPE_MASK) >> 8;

	if (rdes1 & RDES1_IP_HDR_ERROR)
		x->ip_hdr_err++;
	if (rdes1 & RDES1_IP_CSUM_BYPASSED)
		x->ip_csum_bypassed++;
	if (rdes1 & RDES1_IPV4_HEADER)
		x->ipv4_pkt_rcvd++;
	if (rdes1 & RDES1_IPV6_HEADER)
		x->ipv6_pkt_rcvd++;

	if (message_type == RDES_EXT_NO_PTP)
		x->no_ptp_rx_msg_type_ext++;
	else if (message_type == RDES_EXT_SYNC)
		x->ptp_rx_msg_type_sync++;
	else if (message_type == RDES_EXT_FOLLOW_UP)
		x->ptp_rx_msg_type_follow_up++;
	else if (message_type == RDES_EXT_DELAY_REQ)
		x->ptp_rx_msg_type_delay_req++;
	else if (message_type == RDES_EXT_DELAY_RESP)
		x->ptp_rx_msg_type_delay_resp++;
	else if (message_type == RDES_EXT_PDELAY_REQ)
		x->ptp_rx_msg_type_pdelay_req++;
	else if (message_type == RDES_EXT_PDELAY_RESP)
		x->ptp_rx_msg_type_pdelay_resp++;
	else if (message_type == RDES_EXT_PDELAY_FOLLOW_UP)
		x->ptp_rx_msg_type_pdelay_follow_up++;
	else if (message_type == RDES_PTP_ANNOUNCE)
		x->ptp_rx_msg_type_announce++;
	else if (message_type == RDES_PTP_MANAGEMENT)
		x->ptp_rx_msg_type_management++;
	else if (message_type == RDES_PTP_PKT_RESERVED_TYPE)
		x->ptp_rx_msg_pkt_reserved_type++;

	if (rdes1 & RDES1_PTP_PACKET_TYPE)
		x->ptp_frame_type++;
	if (rdes1 & RDES1_PTP_VER)
		x->ptp_ver++;
	if (rdes1 & RDES1_TIMESTAMP_DROPPED)
		x->timestamp_dropped++;

	if (unlikely(rdes2 & RDES2_SA_FILTER_FAIL)) {
		x->sa_rx_filter_fail++;
		ret = discard_frame;
	}
	if (unlikely(rdes2 & RDES2_DA_FILTER_FAIL)) {
		x->da_rx_filter_fail++;
		ret = discard_frame;
	}

	if (rdes2 & RDES2_L3_FILTER_MATCH)
		x->l3_filter_match++;
	if (rdes2 & RDES2_L4_FILTER_MATCH)
		x->l4_filter_match++;
	if ((rdes2 & RDES2_L3_L4_FILT_NB_MATCH_MASK)
	    >> RDES2_L3_L4_FILT_NB_MATCH_SHIFT)
		x->l3_l4_filter_no_match++;

	return ret;
}