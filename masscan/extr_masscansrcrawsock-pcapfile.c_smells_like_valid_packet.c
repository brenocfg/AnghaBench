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

/* Variables and functions */
 unsigned int PCAP32 (unsigned int,unsigned char const*) ; 

__attribute__((used)) static unsigned
smells_like_valid_packet(const unsigned char *px, unsigned length, unsigned byte_order, unsigned link_type)
{
    unsigned secs, usecs, original_length, captured_length;

    if (length < 16)
        return 0;

    secs = PCAP32(byte_order, px+0);
    usecs = PCAP32(byte_order, px+4);
    captured_length = PCAP32(byte_order, px+8);
    original_length = PCAP32(byte_order, px+12);

    if (secs > 0x50000000) return 0; /* after 2010 */
    if (secs < 0x26000000) return 0; /* before 1990 */
    if (usecs > 1000000) return 0;
    if (captured_length > 10000) return 0;
    if (captured_length < 16) return 0;
    if (original_length < captured_length) return 0;
    if (original_length > 10000) return 0;

    if (captured_length + 16 < length) {
        unsigned secs2, usecs2, original_length2, captured_length2;
        const unsigned char *px2 = px + captured_length + 16;

        secs2 = PCAP32(byte_order, px2+0);
        usecs2 = PCAP32(byte_order, px2+4);
        captured_length2 = PCAP32(byte_order, px2+8);
        original_length2 = PCAP32(byte_order, px2+12);

        if (secs2 > 0x50000000)
            return 0;
        if (secs2 < 0x26000000)
            return 0;
        if (usecs2 > 1000000)
            return 0;
        if (captured_length2 > 10000)
            return 0;
        if (captured_length2 < 16)
            return 0;
        if (original_length2 < captured_length2)
            return 0;
        if (original_length2 > 10000)
            return 0;
        return 1;
    } else
    switch (link_type) {
    case 1: /*ethernet*/
        if (px[12] == 0x08 && px[13] == 0x00 && px[14] == 0x45)
            return 1;
    }

    return 0;
}