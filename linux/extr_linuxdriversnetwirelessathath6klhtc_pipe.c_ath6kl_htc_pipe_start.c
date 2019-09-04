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
struct sk_buff {int dummy; } ;
struct htc_target {int /*<<< orphan*/  htc_flags; } ;
struct htc_setup_comp_ext_msg {int /*<<< orphan*/  msg_id; } ;
struct htc_packet {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  ENDPOINT_0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HTC_MSG_SETUP_COMPLETE_EX_ID ; 
 int /*<<< orphan*/  HTC_OP_STATE_SETUP_COMPLETE ; 
 int /*<<< orphan*/  HTC_SERVICE_TX_PACKET_TAG ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int ath6kl_htc_pipe_tx (struct htc_target*,struct htc_packet*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct htc_packet* htc_alloc_txctrl_packet (struct htc_target*) ; 
 int /*<<< orphan*/  htc_config_target_hif_pipe (struct htc_target*) ; 
 int /*<<< orphan*/  memset (struct htc_setup_comp_ext_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_htc_pkt_info (struct htc_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct htc_setup_comp_ext_msg* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int ath6kl_htc_pipe_start(struct htc_target *target)
{
	struct sk_buff *skb;
	struct htc_setup_comp_ext_msg *setup;
	struct htc_packet *packet;

	htc_config_target_hif_pipe(target);

	/* allocate a buffer to send */
	packet = htc_alloc_txctrl_packet(target);
	if (packet == NULL) {
		WARN_ON_ONCE(1);
		return -ENOMEM;
	}

	skb = packet->skb;

	/* assemble setup complete message */
	setup = skb_put(skb, sizeof(*setup));
	memset(setup, 0, sizeof(struct htc_setup_comp_ext_msg));
	setup->msg_id = cpu_to_le16(HTC_MSG_SETUP_COMPLETE_EX_ID);

	ath6kl_dbg(ATH6KL_DBG_HTC, "HTC using TX credit flow control\n");

	set_htc_pkt_info(packet, NULL, (u8 *) setup,
			 sizeof(struct htc_setup_comp_ext_msg),
			 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

	target->htc_flags |= HTC_OP_STATE_SETUP_COMPLETE;

	return ath6kl_htc_pipe_tx(target, packet);
}