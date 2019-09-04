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
struct TYPE_2__ {unsigned int protocol; unsigned int address; int packet_rank; } ;
union nl_packet {unsigned char* rawpkt; TYPE_1__ hdr; } ;
struct ipw_hardware {int dummy; } ;

/* Variables and functions */
 int NL_FIRST_PACKET ; 
 unsigned int NL_FIRST_PACKET_HEADER_SIZE ; 
 unsigned int NL_FOLLOWING_PACKET_HEADER_SIZE ; 
 int NL_LAST_PACKET ; 
#define  TL_PROTOCOLID_COM_CTRL 130 
#define  TL_PROTOCOLID_COM_DATA 129 
#define  TL_PROTOCOLID_SETUP 128 
 int /*<<< orphan*/  handle_received_SETUP_packet (struct ipw_hardware*,unsigned int,unsigned char const*,unsigned int,int) ; 
 int /*<<< orphan*/  queue_received_packet (struct ipw_hardware*,unsigned int,unsigned int,unsigned char const*,unsigned int,int) ; 

__attribute__((used)) static void handle_received_packet(struct ipw_hardware *hw,
				   const union nl_packet *packet,
				   unsigned short len)
{
	unsigned int protocol = packet->hdr.protocol;
	unsigned int address = packet->hdr.address;
	unsigned int header_length;
	const unsigned char *data;
	unsigned int data_len;
	int is_last = packet->hdr.packet_rank & NL_LAST_PACKET;

	if (packet->hdr.packet_rank & NL_FIRST_PACKET)
		header_length = NL_FIRST_PACKET_HEADER_SIZE;
	else
		header_length = NL_FOLLOWING_PACKET_HEADER_SIZE;

	data = packet->rawpkt + header_length;
	data_len = len - header_length;
	switch (protocol) {
	case TL_PROTOCOLID_COM_DATA:
	case TL_PROTOCOLID_COM_CTRL:
		queue_received_packet(hw, protocol, address, data, data_len,
				is_last);
		break;
	case TL_PROTOCOLID_SETUP:
		handle_received_SETUP_packet(hw, address, data, data_len,
				is_last);
		break;
	}
}