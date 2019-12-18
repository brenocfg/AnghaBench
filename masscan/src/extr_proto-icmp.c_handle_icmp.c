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
struct PreprocessedInfo {unsigned int port_src; unsigned int port_dst; int* ip_dst; int* ip_src; int transport_offset; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  ip_ttl; } ;
struct Output {int dummy; } ;
struct DedupTable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PortStatus_Closed ; 
 int /*<<< orphan*/  PortStatus_Open ; 
 int /*<<< orphan*/  Templ_ICMP_echo ; 
 struct DedupTable* dedup_create () ; 
 int /*<<< orphan*/  dedup_is_duplicate (struct DedupTable*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matches_me (struct Output*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  output_report_status (struct Output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_port_unreachable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  syn_cookie (unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
handle_icmp(struct Output *out, time_t timestamp,
            const unsigned char *px, unsigned length,
            struct PreprocessedInfo *parsed,
            uint64_t entropy)
{
    unsigned type = parsed->port_src;
    unsigned code = parsed->port_dst;
    unsigned seqno_me;
    unsigned ip_me;
    unsigned ip_them;
    unsigned cookie;

    /* dedup ICMP echo replies as well as SYN/ACK replies */
    static struct DedupTable *echo_reply_dedup = NULL;


    if (!echo_reply_dedup)
        echo_reply_dedup = dedup_create();

    ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16
            | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;
    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
            | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;

    seqno_me = px[parsed->transport_offset+4]<<24
                | px[parsed->transport_offset+5]<<16
                | px[parsed->transport_offset+6]<<8
                | px[parsed->transport_offset+7]<<0;

    switch (type) {
    case 0: /* ICMP echo reply */
        cookie = (unsigned)syn_cookie(ip_them, Templ_ICMP_echo, ip_me, 0, entropy);
        if ((cookie & 0xFFFFFFFF) != seqno_me)
            return; /* not my response */

        if (dedup_is_duplicate(echo_reply_dedup, ip_them, 0, ip_me, 0))
            break;

        //if (syn_hash(ip_them, Templ_ICMP_echo) != seqno_me)
        //    return; /* not my response */

        /*
         * Report "open" or "existence" of host
         */
        output_report_status(
                            out,
                            timestamp,
                            PortStatus_Open,
                            ip_them,
                            1, /* ip proto */
                            0,
                            0,
                            parsed->ip_ttl,
                            parsed->mac_src);
        break;
    case 3: /* destination unreachable */
        switch (code) {
        case 0: /* net unreachable */
            /* We get these a lot while port scanning, often a flood coming
             * back from broken/misconfigured networks */
            break;
        case 1: /* host unreachable */
            /* This means the router doesn't exist */
            break;
        case 2: /* protocol unreachable */
            /* The host exists, but it doesn't support SCTP */
            break;
        case 3: /* port unreachable */
            if (length - parsed->transport_offset > 8) {
                unsigned ip_me2, ip_them2, port_me2, port_them2;
                unsigned ip_proto;
                int err;

                err = parse_port_unreachable(
                    px + parsed->transport_offset + 8,
                    length - parsed->transport_offset + 8,
                    &ip_me2, &ip_them2, &port_me2, &port_them2,
                    &ip_proto);

                if (err)
                    return;

                if (!matches_me(out, ip_me2, port_me2))
                    return;

                switch (ip_proto) {
                case 6:
                    output_report_status(
                                        out,
                                        timestamp,
                                        PortStatus_Closed,
                                        ip_them2,
                                        ip_proto,
                                        port_them2,
                                        0,
                                        parsed->ip_ttl,
                                        parsed->mac_src);
                    break;
                case 17:
                    output_report_status(
                                        out,
                                        timestamp,
                                        PortStatus_Closed,
                                        ip_them2,
                                        ip_proto,
                                        port_them2,
                                        0,
                                        parsed->ip_ttl,
                                        parsed->mac_src);
                    break;
                case 132:
                    output_report_status(
                                        out,
                                        timestamp,
                                        PortStatus_Closed,
                                        ip_them2,
                                        ip_proto,
                                        port_them2,
                                        0,
                                        parsed->ip_ttl,
                                        parsed->mac_src);
                    break;
                }
            }

        }
        break;
    default:
    ;
    }

}