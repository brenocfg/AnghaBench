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
struct sk_buff {scalar_t__ pkt_type; } ;

/* Variables and functions */
 scalar_t__ PACKET_OUTGOING ; 

__attribute__((used)) static bool skb_is_err_queue(const struct sk_buff *skb)
{
	/* pkt_type of skbs enqueued on the error queue are set to
	 * PACKET_OUTGOING in skb_set_err_queue(). This is only safe to do
	 * in recvmsg, since skbs received on a local socket will never
	 * have a pkt_type of PACKET_OUTGOING.
	 */
	return skb->pkt_type == PACKET_OUTGOING;
}