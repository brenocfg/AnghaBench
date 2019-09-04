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
struct qcom_smd_channel {int remote_state; scalar_t__ state; int pkt_size; int /*<<< orphan*/  fblockread_event; int /*<<< orphan*/  state_change_event; } ;
typedef  int /*<<< orphan*/  pktlen ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GET_RX_CHANNEL_FLAG (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 
 int GET_RX_CHANNEL_INFO (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_TX_CHANNEL_FLAG (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RX_CHANNEL_FLAG (struct qcom_smd_channel*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SMD_CHANNEL_OPENED ; 
 int SMD_PACKET_HEADER_LEN ; 
 int /*<<< orphan*/  fBLOCKREADINTR ; 
 int /*<<< orphan*/  fHEAD ; 
 int /*<<< orphan*/  fSTATE ; 
 int /*<<< orphan*/  fTAIL ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_channel_advance (struct qcom_smd_channel*,int) ; 
 int qcom_smd_channel_get_rx_avail (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  qcom_smd_channel_peek (struct qcom_smd_channel*,int /*<<< orphan*/ *,int) ; 
 int qcom_smd_channel_recv_single (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  qcom_smd_signal_channel (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static bool qcom_smd_channel_intr(struct qcom_smd_channel *channel)
{
	bool need_state_scan = false;
	int remote_state;
	__le32 pktlen;
	int avail;
	int ret;

	/* Handle state changes */
	remote_state = GET_RX_CHANNEL_INFO(channel, state);
	if (remote_state != channel->remote_state) {
		channel->remote_state = remote_state;
		need_state_scan = true;

		wake_up_interruptible_all(&channel->state_change_event);
	}
	/* Indicate that we have seen any state change */
	SET_RX_CHANNEL_FLAG(channel, fSTATE, 0);

	/* Signal waiting qcom_smd_send() about the interrupt */
	if (!GET_TX_CHANNEL_FLAG(channel, fBLOCKREADINTR))
		wake_up_interruptible_all(&channel->fblockread_event);

	/* Don't consume any data until we've opened the channel */
	if (channel->state != SMD_CHANNEL_OPENED)
		goto out;

	/* Indicate that we've seen the new data */
	SET_RX_CHANNEL_FLAG(channel, fHEAD, 0);

	/* Consume data */
	for (;;) {
		avail = qcom_smd_channel_get_rx_avail(channel);

		if (!channel->pkt_size && avail >= SMD_PACKET_HEADER_LEN) {
			qcom_smd_channel_peek(channel, &pktlen, sizeof(pktlen));
			qcom_smd_channel_advance(channel, SMD_PACKET_HEADER_LEN);
			channel->pkt_size = le32_to_cpu(pktlen);
		} else if (channel->pkt_size && avail >= channel->pkt_size) {
			ret = qcom_smd_channel_recv_single(channel);
			if (ret)
				break;
		} else {
			break;
		}
	}

	/* Indicate that we have seen and updated tail */
	SET_RX_CHANNEL_FLAG(channel, fTAIL, 1);

	/* Signal the remote that we've consumed the data (if requested) */
	if (!GET_RX_CHANNEL_FLAG(channel, fBLOCKREADINTR)) {
		/* Ensure ordering of channel info updates */
		wmb();

		qcom_smd_signal_channel(channel);
	}

out:
	return need_state_scan;
}