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
struct sk_buff {int* data; scalar_t__ cb; } ;
struct efx_ptp_match {int* words; int /*<<< orphan*/  state; scalar_t__ expiry; } ;
struct efx_ptp_data {scalar_t__ mode; int /*<<< orphan*/  work; int /*<<< orphan*/  workwq; int /*<<< orphan*/  rxq; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
struct efx_channel {struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MC_CMD_PTP_MODE_V1 ; 
 scalar_t__ MC_CMD_PTP_MODE_V2 ; 
 scalar_t__ MC_CMD_PTP_MODE_V2_ENHANCED ; 
 int /*<<< orphan*/  PKT_EVENT_LIFETIME_MS ; 
 size_t PTP_DPORT_OFFSET ; 
 unsigned int PTP_EVENT_PORT ; 
 int /*<<< orphan*/  PTP_PACKET_STATE_MATCH_UNWANTED ; 
 int /*<<< orphan*/  PTP_PACKET_STATE_UNMATCHED ; 
 int /*<<< orphan*/  PTP_V1_MIN_LENGTH ; 
 int PTP_V1_SEQUENCE_LENGTH ; 
 int PTP_V1_SEQUENCE_OFFSET ; 
 int PTP_V1_UUID_OFFSET ; 
 size_t PTP_V1_VERSION_OFFSET ; 
 int /*<<< orphan*/  PTP_V2_MIN_LENGTH ; 
 int PTP_V2_SEQUENCE_LENGTH ; 
 int PTP_V2_SEQUENCE_OFFSET ; 
 int PTP_V2_UUID_OFFSET ; 
 size_t PTP_V2_VERSION_OFFSET ; 
 unsigned int PTP_VERSION_V1 ; 
 unsigned int PTP_VERSION_V2 ; 
 unsigned int PTP_VERSION_V2_MASK ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static bool efx_ptp_rx(struct efx_channel *channel, struct sk_buff *skb)
{
	struct efx_nic *efx = channel->efx;
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct efx_ptp_match *match = (struct efx_ptp_match *)skb->cb;
	u8 *match_data_012, *match_data_345;
	unsigned int version;
	u8 *data;

	match->expiry = jiffies + msecs_to_jiffies(PKT_EVENT_LIFETIME_MS);

	/* Correct version? */
	if (ptp->mode == MC_CMD_PTP_MODE_V1) {
		if (!pskb_may_pull(skb, PTP_V1_MIN_LENGTH)) {
			return false;
		}
		data = skb->data;
		version = ntohs(*(__be16 *)&data[PTP_V1_VERSION_OFFSET]);
		if (version != PTP_VERSION_V1) {
			return false;
		}

		/* PTP V1 uses all six bytes of the UUID to match the packet
		 * to the timestamp
		 */
		match_data_012 = data + PTP_V1_UUID_OFFSET;
		match_data_345 = data + PTP_V1_UUID_OFFSET + 3;
	} else {
		if (!pskb_may_pull(skb, PTP_V2_MIN_LENGTH)) {
			return false;
		}
		data = skb->data;
		version = data[PTP_V2_VERSION_OFFSET];
		if ((version & PTP_VERSION_V2_MASK) != PTP_VERSION_V2) {
			return false;
		}

		/* The original V2 implementation uses bytes 2-7 of
		 * the UUID to match the packet to the timestamp. This
		 * discards two of the bytes of the MAC address used
		 * to create the UUID (SF bug 33070).  The PTP V2
		 * enhanced mode fixes this issue and uses bytes 0-2
		 * and byte 5-7 of the UUID.
		 */
		match_data_345 = data + PTP_V2_UUID_OFFSET + 5;
		if (ptp->mode == MC_CMD_PTP_MODE_V2) {
			match_data_012 = data + PTP_V2_UUID_OFFSET + 2;
		} else {
			match_data_012 = data + PTP_V2_UUID_OFFSET + 0;
			BUG_ON(ptp->mode != MC_CMD_PTP_MODE_V2_ENHANCED);
		}
	}

	/* Does this packet require timestamping? */
	if (ntohs(*(__be16 *)&data[PTP_DPORT_OFFSET]) == PTP_EVENT_PORT) {
		match->state = PTP_PACKET_STATE_UNMATCHED;

		/* We expect the sequence number to be in the same position in
		 * the packet for PTP V1 and V2
		 */
		BUILD_BUG_ON(PTP_V1_SEQUENCE_OFFSET != PTP_V2_SEQUENCE_OFFSET);
		BUILD_BUG_ON(PTP_V1_SEQUENCE_LENGTH != PTP_V2_SEQUENCE_LENGTH);

		/* Extract UUID/Sequence information */
		match->words[0] = (match_data_012[0]         |
				   (match_data_012[1] << 8)  |
				   (match_data_012[2] << 16) |
				   (match_data_345[0] << 24));
		match->words[1] = (match_data_345[1]         |
				   (match_data_345[2] << 8)  |
				   (data[PTP_V1_SEQUENCE_OFFSET +
					 PTP_V1_SEQUENCE_LENGTH - 1] <<
				    16));
	} else {
		match->state = PTP_PACKET_STATE_MATCH_UNWANTED;
	}

	skb_queue_tail(&ptp->rxq, skb);
	queue_work(ptp->workwq, &ptp->work);

	return true;
}