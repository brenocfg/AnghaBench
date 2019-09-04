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
typedef  unsigned int uint64_t ;
struct TemplatePacket {unsigned int offset_ip; unsigned int offset_tcp; int* packet; size_t length; unsigned int checksum_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int tcp_checksum2 (unsigned char*,unsigned int,unsigned int,size_t) ; 

size_t
tcp_create_packet(
        struct TemplatePacket *tmpl,
        unsigned ip_them, unsigned port_them,
        unsigned ip_me, unsigned port_me,
        unsigned seqno, unsigned ackno,
        unsigned flags,
        const unsigned char *payload, size_t payload_length,
        unsigned char *px, size_t px_length)
{
    unsigned ip_id = ip_them ^ port_them ^ seqno;
    unsigned offset_ip = tmpl->offset_ip;
    unsigned offset_tcp = tmpl->offset_tcp;
    unsigned offset_payload = offset_tcp + ((tmpl->packet[offset_tcp+12]&0xF0)>>2);
    size_t new_length = offset_payload + payload_length;
    uint64_t xsum;
    size_t ip_len = (offset_payload - offset_ip) + payload_length;
    unsigned old_len;

    if (new_length > px_length) {
        fprintf(stderr, "tcp: err generating packet: too much payload\n");
        return 0;
    }

    memcpy(px + 0,              tmpl->packet,   tmpl->length);
    memcpy(px + offset_payload, payload,        payload_length);
    old_len = px[offset_ip+2]<<8 | px[offset_ip+3];

    /*
     * Fill in the empty fields in the IP header and then re-calculate
     * the checksum.
     */
    px[offset_ip+2] = (unsigned char)(ip_len>> 8);
    px[offset_ip+3] = (unsigned char)(ip_len & 0xFF);
    px[offset_ip+4] = (unsigned char)(ip_id >> 8);
    px[offset_ip+5] = (unsigned char)(ip_id & 0xFF);
    px[offset_ip+12] = (unsigned char)((ip_me >> 24) & 0xFF);
    px[offset_ip+13] = (unsigned char)((ip_me >> 16) & 0xFF);
    px[offset_ip+14] = (unsigned char)((ip_me >>  8) & 0xFF);
    px[offset_ip+15] = (unsigned char)((ip_me >>  0) & 0xFF);
    px[offset_ip+16] = (unsigned char)((ip_them >> 24) & 0xFF);
    px[offset_ip+17] = (unsigned char)((ip_them >> 16) & 0xFF);
    px[offset_ip+18] = (unsigned char)((ip_them >>  8) & 0xFF);
    px[offset_ip+19] = (unsigned char)((ip_them >>  0) & 0xFF);

    xsum = tmpl->checksum_ip;
    xsum += (ip_id&0xFFFF);
    xsum += ip_me;
    xsum += ip_them;
    xsum += ip_len - old_len;
    xsum = (xsum >> 16) + (xsum & 0xFFFF);
    xsum = (xsum >> 16) + (xsum & 0xFFFF);
    xsum = ~xsum;

    px[offset_ip+10] = (unsigned char)(xsum >> 8);
    px[offset_ip+11] = (unsigned char)(xsum & 0xFF);

    /*
     * now do the same for TCP
     */
    px[offset_tcp+ 0] = (unsigned char)(port_me >> 8);
    px[offset_tcp+ 1] = (unsigned char)(port_me & 0xFF);
    px[offset_tcp+ 2] = (unsigned char)(port_them >> 8);
    px[offset_tcp+ 3] = (unsigned char)(port_them & 0xFF);
    px[offset_tcp+ 4] = (unsigned char)(seqno >> 24);
    px[offset_tcp+ 5] = (unsigned char)(seqno >> 16);
    px[offset_tcp+ 6] = (unsigned char)(seqno >>  8);
    px[offset_tcp+ 7] = (unsigned char)(seqno >>  0);

    px[offset_tcp+ 8] = (unsigned char)(ackno >> 24);
    px[offset_tcp+ 9] = (unsigned char)(ackno >> 16);
    px[offset_tcp+10] = (unsigned char)(ackno >>  8);
    px[offset_tcp+11] = (unsigned char)(ackno >>  0);

    px[offset_tcp+13] = (unsigned char)flags;

    px[offset_tcp+14] = (unsigned char)(1200>>8);
    px[offset_tcp+15] = (unsigned char)(1200 & 0xFF);

    px[offset_tcp+16] = (unsigned char)(0 >>  8);
    px[offset_tcp+17] = (unsigned char)(0 >>  0);

    xsum = tcp_checksum2(px, tmpl->offset_ip, tmpl->offset_tcp,
                         new_length - tmpl->offset_tcp);
    xsum = ~xsum;

    px[offset_tcp+16] = (unsigned char)(xsum >>  8);
    px[offset_tcp+17] = (unsigned char)(xsum >>  0);

    if (new_length < 60) {
        memset(px+new_length, 0, 60-new_length);
        new_length = 60;
    }
    return new_length;
}