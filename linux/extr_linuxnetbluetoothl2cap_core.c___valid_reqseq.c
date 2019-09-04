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
typedef  scalar_t__ u16 ;
struct l2cap_chan {scalar_t__ expected_ack_seq; int /*<<< orphan*/  next_tx_seq; } ;

/* Variables and functions */
 scalar_t__ __seq_offset (struct l2cap_chan*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool __valid_reqseq(struct l2cap_chan *chan, u16 reqseq)
{
	/* Make sure reqseq is for a packet that has been sent but not acked */
	u16 unacked;

	unacked = __seq_offset(chan, chan->next_tx_seq, chan->expected_ack_seq);
	return __seq_offset(chan, chan->next_tx_seq, reqseq) <= unacked;
}