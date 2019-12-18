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
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PACKET_get_sub_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

int decode_der_length(PACKET *pkt, PACKET *subpkt)
{
    unsigned int byte;

    if (!PACKET_get_1(pkt, &byte))
        return 0;

    if (byte < 0x80)
        return PACKET_get_sub_packet(pkt, subpkt, (size_t)byte);
    if (byte == 0x81)
        return PACKET_get_length_prefixed_1(pkt, subpkt);
    if (byte == 0x82)
        return PACKET_get_length_prefixed_2(pkt, subpkt);

    /* Too large, invalid, or not DER. */
    return 0;
}