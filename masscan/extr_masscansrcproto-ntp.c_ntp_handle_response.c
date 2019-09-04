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
typedef  int /*<<< orphan*/  time_t ;
struct PreprocessedInfo {unsigned int app_offset; int app_length; int* ip_src; int /*<<< orphan*/  ip_ttl; int /*<<< orphan*/  port_src; } ;
struct Output {int dummy; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_NTP ; 
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_string_length (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntp_v2_parse (unsigned char const*,int,struct BannerOutput*,unsigned int*) ; 
 int /*<<< orphan*/  output_report_banner (struct Output*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned
ntp_handle_response(struct Output *out, time_t timestamp,
            const unsigned char *px, unsigned length,
            struct PreprocessedInfo *parsed,
            uint64_t entropy
            )
{
    unsigned ip_them;
    unsigned request_id = 0;
    struct BannerOutput banout[1];
    unsigned offset = parsed->app_offset;
    
    UNUSEDPARM(length);
    UNUSEDPARM(entropy);
    
    if (parsed->app_length < 4)
        return 0;
    
    /* Initialize the "banner output" module that we'll use to print
     * pretty text in place of the raw packet */
    banout_init(banout);
    
    /* Parse the packet */
    switch ((px[offset]>>3)&7) {
        case 2:
            ntp_v2_parse(
               px + parsed->app_offset,    /* incoming  response */
               parsed->app_length,         /* length of  response */
               banout,                     /* banner printing */
               &request_id);               /* syn-cookie info */
            break;
        default:
            banout_release(banout);
            return 0;
    }
    
    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
    | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;
    /*ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16
    | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;*/
    
    /* Validate the "syn-cookie" style information. */
    //seqno = (unsigned)syn_cookie(ip_them, port_them | Templ_UDP, ip_me, port_me);
    //if ((seqno&0x7FFFffff) != request_id)
    //    return 1;
    
    /* Print the banner information, or save to a file, depending */
    output_report_banner(
                         out, timestamp,
                         ip_them, 17, parsed->port_src,
                         PROTO_NTP,
                         parsed->ip_ttl,
                         banout_string(banout, PROTO_NTP),
                         banout_string_length(banout, PROTO_NTP));
    
    /* Free memory for the banner, if there was any allocated */
    banout_release(banout);
    
    return 0;
}