#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packet {int packet_length; TYPE_1__* raw; TYPE_2__* options; scalar_t__ options_valid; } ;
struct TYPE_4__ {int* data; } ;
struct TYPE_3__ {unsigned char* options; scalar_t__ sname; scalar_t__ file; } ;

/* Variables and functions */
 int DHCP_FIXED_NON_UDP ; 
 int /*<<< orphan*/  DHCP_OPTIONS_COOKIE ; 
 size_t DHO_DHCP_OPTION_OVERLOAD ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_option_buffer (struct packet*,unsigned char*,int) ; 

void
parse_options(struct packet *packet)
{
	/* Initially, zero all option pointers. */
	memset(packet->options, 0, sizeof(packet->options));

	/* If we don't see the magic cookie, there's nothing to parse. */
	if (memcmp(packet->raw->options, DHCP_OPTIONS_COOKIE, 4)) {
		packet->options_valid = 0;
		return;
	}

	/*
	 * Go through the options field, up to the end of the packet or
	 * the End field.
	 */
	parse_option_buffer(packet, &packet->raw->options[4],
	    packet->packet_length - DHCP_FIXED_NON_UDP - 4);

	/*
	 * If we parsed a DHCP Option Overload option, parse more
	 * options out of the buffer(s) containing them.
	 */
	if (packet->options_valid &&
	    packet->options[DHO_DHCP_OPTION_OVERLOAD].data) {
		if (packet->options[DHO_DHCP_OPTION_OVERLOAD].data[0] & 1)
			parse_option_buffer(packet,
			    (unsigned char *)packet->raw->file,
			    sizeof(packet->raw->file));
		if (packet->options[DHO_DHCP_OPTION_OVERLOAD].data[0] & 2)
			parse_option_buffer(packet,
			    (unsigned char *)packet->raw->sname,
			    sizeof(packet->raw->sname));
	}
}