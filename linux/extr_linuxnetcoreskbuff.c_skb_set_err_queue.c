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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ PACKET_OUTGOING ; 

__attribute__((used)) static void skb_set_err_queue(struct sk_buff *skb)
{
	/* pkt_type of skbs received on local sockets is never PACKET_OUTGOING.
	 * So, it is safe to (mis)use it to mark skbs on the error queue.
	 */
	skb->pkt_type = PACKET_OUTGOING;
	BUILD_BUG_ON(PACKET_OUTGOING == 0);
}