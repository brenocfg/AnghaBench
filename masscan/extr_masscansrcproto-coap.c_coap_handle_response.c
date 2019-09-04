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
struct PreprocessedInfo {unsigned int port_src; unsigned int port_dst; int* ip_src; int* ip_dst; int /*<<< orphan*/  ip_ttl; } ;
struct Output {int dummy; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  LOG (int,char*) ; 
 int /*<<< orphan*/  PROTO_COAP ; 
 unsigned int Templ_UDP ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_string_length (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int coap_parse (unsigned char const*,unsigned int,struct BannerOutput*,unsigned int*) ; 
 int default_udp_parse (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_report_banner (struct Output*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ syn_cookie (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

unsigned
coap_handle_response(struct Output *out, time_t timestamp,
            const unsigned char *px, unsigned length,
            struct PreprocessedInfo *parsed,
            uint64_t entropy
            )
{
    unsigned ip_them;
    unsigned ip_me;
    unsigned port_them = parsed->port_src;
    unsigned port_me = parsed->port_dst;
    unsigned message_id = 0;
    unsigned cookie;
    struct BannerOutput banout[1];
    bool is_valid;
    
    LOG(1, "[+] COAP\n");
    /* Grab IP addresses */
    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
        | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;
    ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16
        | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;
    
    /* Initialize the "banner output" module that we'll use to print
     * pretty text in place of the raw packet */
    banout_init(banout);
    
    /*
     * Do the protocol parsing
     */
    is_valid = coap_parse(px, length, banout, &message_id);
    
    
    /* Validate the "syn-cookie" style information, which should match the "Message ID field*/
    cookie = (unsigned)syn_cookie(ip_them, port_them | Templ_UDP, ip_me, port_me, entropy);
    /*if ((seqno&0xffff) != message_id)
     goto not_this_protocol;*/
    
    /* See if cookies match. So far, we are allowing responses with the
     * wrong cookie */
    if ((cookie&0xffff) != message_id)
        banout_append(banout, PROTO_COAP, " IP-MISMATCH", AUTO_LEN);

    
    /* Print the banner information, or save to a file, depending */
    if (is_valid) {
        output_report_banner(
            out, timestamp,
            ip_them, 17 /*udp*/, parsed->port_src,
            PROTO_COAP,
            parsed->ip_ttl,
            banout_string(banout, PROTO_COAP),
            banout_string_length(banout, PROTO_COAP));
        banout_release(banout);
        return 0;
    } else {
        banout_release(banout);
        return default_udp_parse(out, timestamp, px, length, parsed, entropy);
    }
}