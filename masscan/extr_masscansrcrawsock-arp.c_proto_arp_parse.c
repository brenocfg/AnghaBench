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
struct ARP_IncomingRequest {int is_valid; unsigned char hardware_type; unsigned char protocol_type; unsigned char hardware_length; unsigned char protocol_length; unsigned char opcode; unsigned char const* mac_src; unsigned char ip_src; unsigned char const* mac_dst; unsigned char ip_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_REMAINING (int) ; 

__attribute__((used)) static void
proto_arp_parse(struct ARP_IncomingRequest *arp,
                const unsigned char px[], unsigned offset, unsigned max)
{

    /*
     * parse the header
     */
    VERIFY_REMAINING(8);
    arp->is_valid = 0; /* not valid yet */

    arp->hardware_type = px[offset]<<8 | px[offset+1];
    arp->protocol_type = px[offset+2]<<8 | px[offset+3];
    arp->hardware_length = px[offset+4];
    arp->protocol_length = px[offset+5];
    arp->opcode = px[offset+6]<<8 | px[offset+7];
    offset += 8;

    /* We only support IPv4 and Ethernet addresses */
    if (arp->protocol_length != 4 && arp->hardware_length != 6)
        return;
    if (arp->protocol_type != 0x0800)
        return;
    if (arp->hardware_type != 1 && arp->hardware_type != 6)
        return;

    /*
     * parse the addresses
     */
    VERIFY_REMAINING(2 * arp->hardware_length + 2 * arp->protocol_length);
    arp->mac_src = px+offset;
    offset += arp->hardware_length;

    arp->ip_src = px[offset+0]<<24 | px[offset+1]<<16 | px[offset+2]<<8 | px[offset+3];
    offset += arp->protocol_length;

    arp->mac_dst = px+offset;
    offset += arp->hardware_length;

    arp->ip_dst = px[offset+0]<<24 | px[offset+1]<<16 | px[offset+2]<<8 | px[offset+3];
    //offset += arp->protocol_length;

    arp->is_valid = 1;
}