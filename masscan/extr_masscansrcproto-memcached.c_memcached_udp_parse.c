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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  stuff ;
struct ProtocolState {int dummy; } ;
struct PreprocessedInfo {unsigned int port_src; unsigned int port_dst; int* ip_src; int* ip_dst; int /*<<< orphan*/  ip_ttl; } ;
struct Output {int dummy; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_MEMCACHED ; 
 unsigned int Templ_UDP ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_string_length (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int default_udp_parse (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcached_tcp_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ProtocolState*,unsigned char const*,unsigned int,struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ProtocolState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_report_banner (struct Output*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ syn_cookie (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

unsigned
memcached_udp_parse(struct Output *out, time_t timestamp,
            const unsigned char *px, unsigned length,
            struct PreprocessedInfo *parsed,
            uint64_t entropy
            )
{
    unsigned ip_them;
    unsigned ip_me;
    unsigned port_them = parsed->port_src;
    unsigned port_me = parsed->port_dst;
    unsigned request_id = 0;
    unsigned sequence_num = 0;
    unsigned total_dgrams = 0;
    unsigned reserved = 0;
    unsigned cookie = 0;
    struct BannerOutput banout[1];

    /* All memcached responses will be at least 8 bytes */
    if (length < 8)
        return 0;

    /*
    The frame header is 8 bytes long, as follows (all values are 16-bit integers
    in network byte order, high byte first):

    0-1 Request ID
    2-3 Sequence number
    4-5 Total number of datagrams in this message
    6-7 Reserved for future use; must be 0
    */
    request_id = px[0]<<8 | px[1];
    sequence_num = px[2]<<8 | px[3];
    total_dgrams = px[4]<<8 | px[5];
    reserved = px[6]<<8 | px[7];

    /* Ignore high sequence numbers. This should be zero normally */
    if (sequence_num > 100)
        goto not_memcached;

    /* Ignore too many dgrams, should be one normally */
    if (total_dgrams > 100)
        goto not_memcached;

    /* Make sure reserved field is zero */
    if (reserved != 0)
        goto not_memcached;

    /* Grab IP addresses */
    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
            | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;
    ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16
            | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;

    /* Validate the "syn-cookie" style information. In the case of SNMP,
     * this will be held in the "request-id" field. If the cookie isn't
     * a good one, then we'll ignore the response */
    cookie = (unsigned)syn_cookie(ip_them, port_them | Templ_UDP, ip_me, port_me, entropy);
    /*if ((seqno&0xffff) != request_id)
        return 1;*/

    /* Initialize the "banner output" module that we'll use to print
     * pretty text in place of the raw packet */
    banout_init(banout);

    /* Parse the remainder of the packet as if this were TCP */
    {
        struct ProtocolState stuff[1];

        memset(stuff, 0, sizeof(stuff[0]));

        memcached_tcp_parse(
            0, 0,
            stuff, px+8, length-8, banout, 
            0);
    }

    if ((cookie&0xffff) != request_id)
        banout_append(banout, PROTO_MEMCACHED, " IP-MISMATCH", AUTO_LEN);
            
    /* Print the banner information, or save to a file, depending */
    output_report_banner(
        out, timestamp,
        ip_them, 17 /*udp*/, parsed->port_src,
        PROTO_MEMCACHED,
        parsed->ip_ttl,
        banout_string(banout, PROTO_MEMCACHED),
        banout_string_length(banout, PROTO_MEMCACHED));

    /* Free memory for the banner, if there was any allocated */
    banout_release(banout);

    return 0;
    
not_memcached:
    return default_udp_parse(out, timestamp, px, length, parsed, entropy);
}