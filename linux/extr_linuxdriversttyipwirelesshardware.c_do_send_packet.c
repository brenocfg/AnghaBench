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
struct TYPE_2__ {unsigned char length_lsb; unsigned char length_msb; int /*<<< orphan*/  packet_rank; int /*<<< orphan*/  address; int /*<<< orphan*/  protocol; } ;
union nl_packet {scalar_t__ rawpkt; TYPE_1__ hdr_first; } ;
struct ipw_tx_packet {int length; unsigned short offset; scalar_t__ fragment_count; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* packet_callback ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  queue; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  protocol; } ;
struct ipw_hardware {unsigned short ll_mtu; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_queued; int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_FIRST_PACKET ; 
 unsigned short NL_FIRST_PACKET_HEADER_SIZE ; 
 unsigned short NL_FOLLOWING_PACKET_HEADER_SIZE ; 
 int /*<<< orphan*/  NL_LAST_PACKET ; 
 int /*<<< orphan*/  do_send_fragment (struct ipw_hardware*,scalar_t__,unsigned short) ; 
 int /*<<< orphan*/  kfree (struct ipw_tx_packet*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_send_packet(struct ipw_hardware *hw, struct ipw_tx_packet *packet)
{
	unsigned short fragment_data_len;
	unsigned short data_left = packet->length - packet->offset;
	unsigned short header_size;
	union nl_packet pkt;

	header_size =
	    (packet->fragment_count == 0)
	    ? NL_FIRST_PACKET_HEADER_SIZE
	    : NL_FOLLOWING_PACKET_HEADER_SIZE;
	fragment_data_len = hw->ll_mtu - header_size;
	if (data_left < fragment_data_len)
		fragment_data_len = data_left;

	/*
	 * hdr_first is now in machine bitfield order, which will be swapped
	 * to le just before it goes to hw
	 */
	pkt.hdr_first.protocol = packet->protocol;
	pkt.hdr_first.address = packet->dest_addr;
	pkt.hdr_first.packet_rank = 0;

	/* First packet? */
	if (packet->fragment_count == 0) {
		pkt.hdr_first.packet_rank |= NL_FIRST_PACKET;
		pkt.hdr_first.length_lsb = (unsigned char) packet->length;
		pkt.hdr_first.length_msb =
			(unsigned char) (packet->length >> 8);
	}

	memcpy(pkt.rawpkt + header_size,
	       ((unsigned char *) packet) + sizeof(struct ipw_tx_packet) +
	       packet->offset, fragment_data_len);
	packet->offset += fragment_data_len;
	packet->fragment_count++;

	/* Last packet? (May also be first packet.) */
	if (packet->offset == packet->length)
		pkt.hdr_first.packet_rank |= NL_LAST_PACKET;
	do_send_fragment(hw, pkt.rawpkt, header_size + fragment_data_len);

	/* If this packet has unsent data, then re-queue it. */
	if (packet->offset < packet->length) {
		/*
		 * Re-queue it at the head of the highest priority queue so
		 * it goes before all other packets
		 */
		unsigned long flags;

		spin_lock_irqsave(&hw->lock, flags);
		list_add(&packet->queue, &hw->tx_queue[0]);
		hw->tx_queued++;
		spin_unlock_irqrestore(&hw->lock, flags);
	} else {
		if (packet->packet_callback)
			packet->packet_callback(packet->callback_data,
					packet->length);
		kfree(packet);
	}
}