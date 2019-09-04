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
struct TYPE_3__ {int err_l2_type; int layer34_pkt_type; scalar_t__ l4_filter_match; scalar_t__ l3_filter_match; scalar_t__ hash_filter_pass; scalar_t__ da_filter_fail; scalar_t__ sa_filter_fail; scalar_t__ vlan_filter_match; scalar_t__ err_summary; } ;
struct TYPE_4__ {TYPE_1__ rx_wb_des23; } ;
struct sxgbe_rx_norm_desc {TYPE_2__ rdes23; } ;
struct sxgbe_extra_stats {int /*<<< orphan*/  l4_filter_match; int /*<<< orphan*/  l3_filter_match; int /*<<< orphan*/  hash_filter_pass; int /*<<< orphan*/  da_filter_fail; int /*<<< orphan*/  sa_filter_fail; int /*<<< orphan*/  vlan_filter_match; int /*<<< orphan*/  ip6_unknown_pkt; int /*<<< orphan*/  ip6_icmp_pkt; int /*<<< orphan*/  ip6_udp_pkt; int /*<<< orphan*/  ip6_tcp_pkt; int /*<<< orphan*/  ip4_unknown_pkt; int /*<<< orphan*/  ip4_icmp_pkt; int /*<<< orphan*/  ip4_udp_pkt; int /*<<< orphan*/  ip4_tcp_pkt; int /*<<< orphan*/  not_ip_pkt; int /*<<< orphan*/  dvlan_ocvlan_icvlan_pkt; int /*<<< orphan*/  dvlan_osvlan_icvlan_pkt; int /*<<< orphan*/  dvlan_osvlan_isvlan_pkt; int /*<<< orphan*/  cvlan_tag_pkt; int /*<<< orphan*/  svlan_tag_pkt; int /*<<< orphan*/  other_pkt; int /*<<< orphan*/  untag_okt; int /*<<< orphan*/  oam_pkt; int /*<<< orphan*/  arp_pkt; int /*<<< orphan*/  dcb_ctl_pkt; int /*<<< orphan*/  mac_ctl_pkt; int /*<<< orphan*/  len_pkt; int /*<<< orphan*/  overflow_error; int /*<<< orphan*/  ip_payload_err; int /*<<< orphan*/  ip_hdr_err; int /*<<< orphan*/  rx_gaint_pkt_err; int /*<<< orphan*/  rx_crc_err; int /*<<< orphan*/  rx_watchdog_err; int /*<<< orphan*/  rx_code_gmii_err; } ;

/* Variables and functions */
 int CHECKSUM_NONE ; 
 int CHECKSUM_UNNECESSARY ; 
 int EINVAL ; 
#define  RX_ARP_PKT 156 
#define  RX_CRC_ERR 155 
#define  RX_CVLAN_PKT 154 
#define  RX_DCBCTL_PKT 153 
#define  RX_DVLAN_OCVLAN_ICVLAN_PKT 152 
#define  RX_DVLAN_OCVLAN_ISVLAN_PKT 151 
#define  RX_DVLAN_OSVLAN_ICVLAN_PKT 150 
#define  RX_DVLAN_OSVLAN_ISVLAN_PKT 149 
#define  RX_GAINT_ERR 148 
#define  RX_GMII_ERR 147 
#define  RX_IPV4_ICMP_PKT 146 
#define  RX_IPV4_TCP_PKT 145 
#define  RX_IPV4_UDP_PKT 144 
#define  RX_IPV4_UNKNOWN_PKT 143 
#define  RX_IPV6_ICMP_PKT 142 
#define  RX_IPV6_TCP_PKT 141 
#define  RX_IPV6_UDP_PKT 140 
#define  RX_IPV6_UNKNOWN_PKT 139 
#define  RX_IP_HDR_ERR 138 
#define  RX_LEN_PKT 137 
#define  RX_MACCTL_PKT 136 
#define  RX_NOT_IP_PKT 135 
#define  RX_OAM_PKT 134 
#define  RX_OTHER_PKT 133 
#define  RX_OVERFLOW_ERR 132 
#define  RX_PAYLOAD_ERR 131 
#define  RX_SVLAN_PKT 130 
#define  RX_UNTAG_PKT 129 
#define  RX_WATCHDOG_ERR 128 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int sxgbe_rx_wbstatus(struct sxgbe_rx_norm_desc *p,
			     struct sxgbe_extra_stats *x, int *checksum)
{
	int status = 0;

	*checksum = CHECKSUM_UNNECESSARY;
	if (p->rdes23.rx_wb_des23.err_summary) {
		switch (p->rdes23.rx_wb_des23.err_l2_type) {
		case RX_GMII_ERR:
			status = -EINVAL;
			x->rx_code_gmii_err++;
			break;
		case RX_WATCHDOG_ERR:
			status = -EINVAL;
			x->rx_watchdog_err++;
			break;
		case RX_CRC_ERR:
			status = -EINVAL;
			x->rx_crc_err++;
			break;
		case RX_GAINT_ERR:
			status = -EINVAL;
			x->rx_gaint_pkt_err++;
			break;
		case RX_IP_HDR_ERR:
			*checksum = CHECKSUM_NONE;
			x->ip_hdr_err++;
			break;
		case RX_PAYLOAD_ERR:
			*checksum = CHECKSUM_NONE;
			x->ip_payload_err++;
			break;
		case RX_OVERFLOW_ERR:
			status = -EINVAL;
			x->overflow_error++;
			break;
		default:
			pr_err("Invalid Error type\n");
			break;
		}
	} else {
		switch (p->rdes23.rx_wb_des23.err_l2_type) {
		case RX_LEN_PKT:
			x->len_pkt++;
			break;
		case RX_MACCTL_PKT:
			x->mac_ctl_pkt++;
			break;
		case RX_DCBCTL_PKT:
			x->dcb_ctl_pkt++;
			break;
		case RX_ARP_PKT:
			x->arp_pkt++;
			break;
		case RX_OAM_PKT:
			x->oam_pkt++;
			break;
		case RX_UNTAG_PKT:
			x->untag_okt++;
			break;
		case RX_OTHER_PKT:
			x->other_pkt++;
			break;
		case RX_SVLAN_PKT:
			x->svlan_tag_pkt++;
			break;
		case RX_CVLAN_PKT:
			x->cvlan_tag_pkt++;
			break;
		case RX_DVLAN_OCVLAN_ICVLAN_PKT:
			x->dvlan_ocvlan_icvlan_pkt++;
			break;
		case RX_DVLAN_OSVLAN_ISVLAN_PKT:
			x->dvlan_osvlan_isvlan_pkt++;
			break;
		case RX_DVLAN_OSVLAN_ICVLAN_PKT:
			x->dvlan_osvlan_icvlan_pkt++;
			break;
		case RX_DVLAN_OCVLAN_ISVLAN_PKT:
			x->dvlan_ocvlan_icvlan_pkt++;
			break;
		default:
			pr_err("Invalid L2 Packet type\n");
			break;
		}
	}

	/* L3/L4 Pkt type */
	switch (p->rdes23.rx_wb_des23.layer34_pkt_type) {
	case RX_NOT_IP_PKT:
		x->not_ip_pkt++;
		break;
	case RX_IPV4_TCP_PKT:
		x->ip4_tcp_pkt++;
		break;
	case RX_IPV4_UDP_PKT:
		x->ip4_udp_pkt++;
		break;
	case RX_IPV4_ICMP_PKT:
		x->ip4_icmp_pkt++;
		break;
	case RX_IPV4_UNKNOWN_PKT:
		x->ip4_unknown_pkt++;
		break;
	case RX_IPV6_TCP_PKT:
		x->ip6_tcp_pkt++;
		break;
	case RX_IPV6_UDP_PKT:
		x->ip6_udp_pkt++;
		break;
	case RX_IPV6_ICMP_PKT:
		x->ip6_icmp_pkt++;
		break;
	case RX_IPV6_UNKNOWN_PKT:
		x->ip6_unknown_pkt++;
		break;
	default:
		pr_err("Invalid L3/L4 Packet type\n");
		break;
	}

	/* Filter */
	if (p->rdes23.rx_wb_des23.vlan_filter_match)
		x->vlan_filter_match++;

	if (p->rdes23.rx_wb_des23.sa_filter_fail) {
		status = -EINVAL;
		x->sa_filter_fail++;
	}
	if (p->rdes23.rx_wb_des23.da_filter_fail) {
		status = -EINVAL;
		x->da_filter_fail++;
	}
	if (p->rdes23.rx_wb_des23.hash_filter_pass)
		x->hash_filter_pass++;

	if (p->rdes23.rx_wb_des23.l3_filter_match)
		x->l3_filter_match++;

	if (p->rdes23.rx_wb_des23.l4_filter_match)
		x->l4_filter_match++;

	return status;
}