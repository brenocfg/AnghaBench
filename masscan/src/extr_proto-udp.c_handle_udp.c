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
struct PreprocessedInfo {unsigned int port_src; int* ip_src; unsigned int app_length; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  app_offset; } ;
struct Output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PortStatus_Open ; 
 unsigned int coap_handle_response (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int default_udp_parse (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int handle_dns (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int handle_nbtstat (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int handle_snmp (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int handle_zeroaccess (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int memcached_udp_parse (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 unsigned int ntp_handle_response (struct Output*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,struct PreprocessedInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_report_status (struct Output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
handle_udp(struct Output *out, time_t timestamp,
        const unsigned char *px, unsigned length, 
        struct PreprocessedInfo *parsed, uint64_t entropy)
{
    unsigned ip_them;
    unsigned port_them = parsed->port_src;
    unsigned status = 0;

    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
            | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;



    switch (port_them) {
        case 53: /* DNS - Domain Name System (amplifier) */
            status = handle_dns(out, timestamp, px, length, parsed, entropy);
            break;
        case 123: /* NTP - Network Time Protocol (amplifier) */
            status = ntp_handle_response(out, timestamp, px, length, parsed, entropy);
            break;
        case 137: /* NetBIOS (amplifier) */
            status = handle_nbtstat(out, timestamp, px, length, parsed, entropy);
            break;
        case 161: /* SNMP - Simple Network Managment Protocol (amplifier) */
            status = handle_snmp(out, timestamp, px, length, parsed, entropy);
            break;
        case 5683:
            status = coap_handle_response(out, timestamp, px + parsed->app_offset, parsed->app_length, parsed, entropy);
            break;
        case 11211: /* memcached (amplifier) */
            px += parsed->app_offset;
            length = parsed->app_length;
            status = memcached_udp_parse(out, timestamp, px, length, parsed, entropy);
            break;
        case 16464:
        case 16465:
        case 16470:
        case 16471:
            status = handle_zeroaccess(out, timestamp, px, length, parsed, entropy);
            break;
        default:
            px += parsed->app_offset;
            length = parsed->app_length;
            status = default_udp_parse(out, timestamp, px, length, parsed, entropy);
            break;
    }

    if (status == 0)
        output_report_status(
                        out,
                        timestamp,
                        PortStatus_Open,
                        ip_them,
                        17, /* ip proto = udp */
                        port_them,
                        0,
                        0,
                        parsed->mac_src);

}