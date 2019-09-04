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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
struct PreprocessedInfo {unsigned int port_src; unsigned int port_dst; int* ip_src; int* ip_dst; int /*<<< orphan*/  ip_ttl; scalar_t__ app_length; scalar_t__ app_offset; } ;
struct Output {int dummy; } ;
struct DNS_Incoming {int id; int qr; scalar_t__ rcode; int qdcount; int ancount; int rr_count; unsigned int* rr_offset; } ;

/* Variables and functions */
 unsigned int Templ_UDP ; 
 unsigned int dns_name_skip (unsigned char const*,unsigned int,unsigned int) ; 
 int handle_nbtstat_rr (struct Output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  proto_dns_parse (struct DNS_Incoming*,unsigned char const*,scalar_t__,scalar_t__) ; 
 scalar_t__ syn_cookie (unsigned int,unsigned int,unsigned int,unsigned int,int) ; 

unsigned
handle_nbtstat(struct Output *out, time_t timestamp,
    const unsigned char *px, unsigned length, 
    struct PreprocessedInfo *parsed,
    uint64_t entropy)
{
    unsigned ip_them;
    unsigned ip_me;
    unsigned port_them = parsed->port_src;
    unsigned port_me = parsed->port_dst;
    struct DNS_Incoming dns[1];
    unsigned offset;
    uint64_t seqno;

    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
            | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;
    ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16
            | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;

    seqno = (unsigned)syn_cookie(ip_them, port_them | Templ_UDP, ip_me, port_me, entropy);

    proto_dns_parse(dns, px, parsed->app_offset, parsed->app_offset + parsed->app_length);

    if ((seqno & 0xFFFF) != dns->id)
        return 1;

    if (dns->qr != 1)
        return 0;
    if (dns->rcode != 0)
        return 0;
    if (dns->qdcount > 1)
        return 0;
    if (dns->ancount < 1)
        return 0;
    if (dns->rr_count < 1)
        return 0;


    offset = dns->rr_offset[dns->qdcount];
    offset = dns_name_skip(px, offset, length);
    if (offset + 10 >= length)
        return 0;

    {
        unsigned type = px[offset+0]<<8 | px[offset+1];
        unsigned xclass = px[offset+2]<<8 | px[offset+3];
        unsigned rrlen = px[offset+8]<<8 | px[offset+9];
        unsigned txtlen = px[offset+10];

        if (rrlen == 0 || txtlen > rrlen-1)
            return 0;
        if (type != 0x21 || xclass != 1)
            return 0;

        offset += 10;

        return handle_nbtstat_rr(out, timestamp, parsed->ip_ttl,
                                    px + offset,
                                    length - offset,
                                    ip_them,
                                    port_them);
    }

}