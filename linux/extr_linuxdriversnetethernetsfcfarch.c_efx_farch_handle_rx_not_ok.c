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
typedef  int /*<<< orphan*/  u16 ;
struct efx_rx_queue {struct efx_nic* efx; } ;
struct efx_nic {TYPE_1__* net_dev; int /*<<< orphan*/  loopback_selftest; } ;
struct efx_channel {int /*<<< orphan*/  n_rx_tcp_udp_chksum_err; int /*<<< orphan*/  n_rx_ip_hdr_chksum_err; int /*<<< orphan*/  n_rx_tobe_disc; int /*<<< orphan*/  n_rx_frm_trunc; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 void* EFX_QWORD_FIELD (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_RX_PKT_DISCARD ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_BUF_OWNER_ID_ERR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_ETH_CRC_ERR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_FRM_TRUNC ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_HDR_TYPE ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_IP_HDR_CHKSUM_ERR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_MCAST_PKT ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_PAUSE_FRM_ERR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_PKT_TYPE ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_TCP_UDP_CHKSUM_ERR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_TOBE_DISC ; 
 int NETIF_F_RXALL ; 
 struct efx_channel* efx_rx_queue_channel (struct efx_rx_queue*) ; 

__attribute__((used)) static u16 efx_farch_handle_rx_not_ok(struct efx_rx_queue *rx_queue,
				      const efx_qword_t *event)
{
	struct efx_channel *channel = efx_rx_queue_channel(rx_queue);
	struct efx_nic *efx = rx_queue->efx;
	bool rx_ev_buf_owner_id_err, rx_ev_ip_hdr_chksum_err;
	bool rx_ev_tcp_udp_chksum_err, rx_ev_eth_crc_err;
	bool rx_ev_frm_trunc, rx_ev_tobe_disc;
	bool rx_ev_other_err, rx_ev_pause_frm;
	bool rx_ev_hdr_type, rx_ev_mcast_pkt;
	unsigned rx_ev_pkt_type;

	rx_ev_hdr_type = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_HDR_TYPE);
	rx_ev_mcast_pkt = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_MCAST_PKT);
	rx_ev_tobe_disc = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_TOBE_DISC);
	rx_ev_pkt_type = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_PKT_TYPE);
	rx_ev_buf_owner_id_err = EFX_QWORD_FIELD(*event,
						 FSF_AZ_RX_EV_BUF_OWNER_ID_ERR);
	rx_ev_ip_hdr_chksum_err = EFX_QWORD_FIELD(*event,
						  FSF_AZ_RX_EV_IP_HDR_CHKSUM_ERR);
	rx_ev_tcp_udp_chksum_err = EFX_QWORD_FIELD(*event,
						   FSF_AZ_RX_EV_TCP_UDP_CHKSUM_ERR);
	rx_ev_eth_crc_err = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_ETH_CRC_ERR);
	rx_ev_frm_trunc = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_FRM_TRUNC);
	rx_ev_pause_frm = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_PAUSE_FRM_ERR);

	/* Every error apart from tobe_disc and pause_frm */
	rx_ev_other_err = (rx_ev_tcp_udp_chksum_err |
			   rx_ev_buf_owner_id_err | rx_ev_eth_crc_err |
			   rx_ev_frm_trunc | rx_ev_ip_hdr_chksum_err);

	/* Count errors that are not in MAC stats.  Ignore expected
	 * checksum errors during self-test. */
	if (rx_ev_frm_trunc)
		++channel->n_rx_frm_trunc;
	else if (rx_ev_tobe_disc)
		++channel->n_rx_tobe_disc;
	else if (!efx->loopback_selftest) {
		if (rx_ev_ip_hdr_chksum_err)
			++channel->n_rx_ip_hdr_chksum_err;
		else if (rx_ev_tcp_udp_chksum_err)
			++channel->n_rx_tcp_udp_chksum_err;
	}

	/* TOBE_DISC is expected on unicast mismatches; don't print out an
	 * error message.  FRM_TRUNC indicates RXDP dropped the packet due
	 * to a FIFO overflow.
	 */
#ifdef DEBUG
	if (rx_ev_other_err && net_ratelimit()) {
		netif_dbg(efx, rx_err, efx->net_dev,
			  " RX queue %d unexpected RX event "
			  EFX_QWORD_FMT "%s%s%s%s%s%s%s\n",
			  efx_rx_queue_index(rx_queue), EFX_QWORD_VAL(*event),
			  rx_ev_buf_owner_id_err ? " [OWNER_ID_ERR]" : "",
			  rx_ev_ip_hdr_chksum_err ?
			  " [IP_HDR_CHKSUM_ERR]" : "",
			  rx_ev_tcp_udp_chksum_err ?
			  " [TCP_UDP_CHKSUM_ERR]" : "",
			  rx_ev_eth_crc_err ? " [ETH_CRC_ERR]" : "",
			  rx_ev_frm_trunc ? " [FRM_TRUNC]" : "",
			  rx_ev_tobe_disc ? " [TOBE_DISC]" : "",
			  rx_ev_pause_frm ? " [PAUSE]" : "");
	}
#endif

	if (efx->net_dev->features & NETIF_F_RXALL)
		/* don't discard frame for CRC error */
		rx_ev_eth_crc_err = false;

	/* The frame must be discarded if any of these are true. */
	return (rx_ev_eth_crc_err | rx_ev_frm_trunc |
		rx_ev_tobe_disc | rx_ev_pause_frm) ?
		EFX_RX_PKT_DISCARD : 0;
}