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
typedef  int /*<<< orphan*/  u32 ;
struct htc_target {scalar_t__ htc_tgt_ver; scalar_t__ msg_per_bndl_max; } ;
struct htc_setup_comp_msg {scalar_t__ msg_per_rxbndl; void* msg_id; int /*<<< orphan*/  flags; } ;
struct htc_setup_comp_ext_msg {scalar_t__ msg_per_rxbndl; void* msg_id; int /*<<< orphan*/  flags; } ;
struct htc_packet {int /*<<< orphan*/ * completion; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HTC_MSG_SETUP_COMPLETE_EX_ID ; 
 int /*<<< orphan*/  HTC_MSG_SETUP_COMPLETE_ID ; 
 int /*<<< orphan*/  HTC_SERVICE_TX_PACKET_TAG ; 
 int /*<<< orphan*/  HTC_SETUP_COMP_FLG_RX_BNDL_EN ; 
 scalar_t__ HTC_VERSION_2P1 ; 
 int ath6kl_htc_tx_issue (struct htc_target*,struct htc_packet*) ; 
 int /*<<< orphan*/  ath6kl_htc_tx_prep_pkt (struct htc_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct htc_packet* htc_get_control_buf (struct htc_target*,int) ; 
 int /*<<< orphan*/  htc_reclaim_txctrl_buf (struct htc_target*,struct htc_packet*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct htc_setup_comp_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_htc_pkt_info (struct htc_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int htc_setup_tx_complete(struct htc_target *target)
{
	struct htc_packet *send_pkt = NULL;
	int status;

	send_pkt = htc_get_control_buf(target, true);

	if (!send_pkt)
		return -ENOMEM;

	if (target->htc_tgt_ver >= HTC_VERSION_2P1) {
		struct htc_setup_comp_ext_msg *setup_comp_ext;
		u32 flags = 0;

		setup_comp_ext =
		    (struct htc_setup_comp_ext_msg *)send_pkt->buf;
		memset(setup_comp_ext, 0, sizeof(*setup_comp_ext));
		setup_comp_ext->msg_id =
			cpu_to_le16(HTC_MSG_SETUP_COMPLETE_EX_ID);

		if (target->msg_per_bndl_max > 0) {
			/* Indicate HTC bundling to the target */
			flags |= HTC_SETUP_COMP_FLG_RX_BNDL_EN;
			setup_comp_ext->msg_per_rxbndl =
						target->msg_per_bndl_max;
		}

		memcpy(&setup_comp_ext->flags, &flags,
		       sizeof(setup_comp_ext->flags));
		set_htc_pkt_info(send_pkt, NULL, (u8 *) setup_comp_ext,
				 sizeof(struct htc_setup_comp_ext_msg),
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

	} else {
		struct htc_setup_comp_msg *setup_comp;
		setup_comp = (struct htc_setup_comp_msg *)send_pkt->buf;
		memset(setup_comp, 0, sizeof(struct htc_setup_comp_msg));
		setup_comp->msg_id = cpu_to_le16(HTC_MSG_SETUP_COMPLETE_ID);
		set_htc_pkt_info(send_pkt, NULL, (u8 *) setup_comp,
				 sizeof(struct htc_setup_comp_msg),
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);
	}

	/* we want synchronous operation */
	send_pkt->completion = NULL;
	ath6kl_htc_tx_prep_pkt(send_pkt, 0, 0, 0);
	status = ath6kl_htc_tx_issue(target, send_pkt);
	htc_reclaim_txctrl_buf(target, send_pkt);

	return status;
}