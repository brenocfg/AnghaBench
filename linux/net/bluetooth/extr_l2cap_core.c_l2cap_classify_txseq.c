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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ head; } ;
struct l2cap_chan {scalar_t__ expected_tx_seq; scalar_t__ rx_state; int tx_win; int tx_win_max; int /*<<< orphan*/  last_acked_seq; TYPE_1__ srej_list; int /*<<< orphan*/  srej_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 scalar_t__ L2CAP_RX_STATE_SREJ_SENT ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_DUPLICATE ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_DUPLICATE_SREJ ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_EXPECTED ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_EXPECTED_SREJ ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_INVALID ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_INVALID_IGNORE ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_UNEXPECTED ; 
 int /*<<< orphan*/  L2CAP_TXSEQ_UNEXPECTED_SREJ ; 
 int __seq_offset (struct l2cap_chan*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ l2cap_seq_list_contains (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static u8 l2cap_classify_txseq(struct l2cap_chan *chan, u16 txseq)
{
	BT_DBG("chan %p, txseq %d", chan, txseq);

	BT_DBG("last_acked_seq %d, expected_tx_seq %d", chan->last_acked_seq,
	       chan->expected_tx_seq);

	if (chan->rx_state == L2CAP_RX_STATE_SREJ_SENT) {
		if (__seq_offset(chan, txseq, chan->last_acked_seq) >=
		    chan->tx_win) {
			/* See notes below regarding "double poll" and
			 * invalid packets.
			 */
			if (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) {
				BT_DBG("Invalid/Ignore - after SREJ");
				return L2CAP_TXSEQ_INVALID_IGNORE;
			} else {
				BT_DBG("Invalid - in window after SREJ sent");
				return L2CAP_TXSEQ_INVALID;
			}
		}

		if (chan->srej_list.head == txseq) {
			BT_DBG("Expected SREJ");
			return L2CAP_TXSEQ_EXPECTED_SREJ;
		}

		if (l2cap_ertm_seq_in_queue(&chan->srej_q, txseq)) {
			BT_DBG("Duplicate SREJ - txseq already stored");
			return L2CAP_TXSEQ_DUPLICATE_SREJ;
		}

		if (l2cap_seq_list_contains(&chan->srej_list, txseq)) {
			BT_DBG("Unexpected SREJ - not requested");
			return L2CAP_TXSEQ_UNEXPECTED_SREJ;
		}
	}

	if (chan->expected_tx_seq == txseq) {
		if (__seq_offset(chan, txseq, chan->last_acked_seq) >=
		    chan->tx_win) {
			BT_DBG("Invalid - txseq outside tx window");
			return L2CAP_TXSEQ_INVALID;
		} else {
			BT_DBG("Expected");
			return L2CAP_TXSEQ_EXPECTED;
		}
	}

	if (__seq_offset(chan, txseq, chan->last_acked_seq) <
	    __seq_offset(chan, chan->expected_tx_seq, chan->last_acked_seq)) {
		BT_DBG("Duplicate - expected_tx_seq later than txseq");
		return L2CAP_TXSEQ_DUPLICATE;
	}

	if (__seq_offset(chan, txseq, chan->last_acked_seq) >= chan->tx_win) {
		/* A source of invalid packets is a "double poll" condition,
		 * where delays cause us to send multiple poll packets.  If
		 * the remote stack receives and processes both polls,
		 * sequence numbers can wrap around in such a way that a
		 * resent frame has a sequence number that looks like new data
		 * with a sequence gap.  This would trigger an erroneous SREJ
		 * request.
		 *
		 * Fortunately, this is impossible with a tx window that's
		 * less than half of the maximum sequence number, which allows
		 * invalid frames to be safely ignored.
		 *
		 * With tx window sizes greater than half of the tx window
		 * maximum, the frame is invalid and cannot be ignored.  This
		 * causes a disconnect.
		 */

		if (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) {
			BT_DBG("Invalid/Ignore - txseq outside tx window");
			return L2CAP_TXSEQ_INVALID_IGNORE;
		} else {
			BT_DBG("Invalid - txseq outside tx window");
			return L2CAP_TXSEQ_INVALID;
		}
	} else {
		BT_DBG("Unexpected - txseq indicates missing frames");
		return L2CAP_TXSEQ_UNEXPECTED;
	}
}