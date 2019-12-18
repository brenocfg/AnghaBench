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
struct PreprocessedInfo {unsigned int port_src; unsigned int transport_offset; int* ip_src; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  ip_ttl; } ;
struct Output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PortStatus_Closed ; 
 int /*<<< orphan*/  PortStatus_Open ; 
 int /*<<< orphan*/  UNUSEDPARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_report_status (struct Output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
handle_sctp(struct Output *out, time_t timestamp,
            const unsigned char *px, unsigned length, 
            unsigned cookie,
            struct PreprocessedInfo *parsed,
            uint64_t entropy)
{
    unsigned ip_them;
    unsigned port_them = parsed->port_src;
    unsigned verification_tag;
    unsigned offset = parsed->transport_offset;

    UNUSEDPARM(entropy);

    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16
            | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;

    verification_tag = px[offset + 4] << 24 | px[offset + 5] << 16 |
                        px[offset + 6] << 8 | px[offset + 7];
    if (cookie != verification_tag)
        return;

    if (offset + 16 > length)
        return;

    switch (px[offset + 12]) {
    case 2: /* init ack */
        output_report_status(
                        out,
                        timestamp,
                        PortStatus_Open,
                        ip_them,
                        132, /* ip proto = sctp */
                        port_them,
                        0,
                        parsed->ip_ttl,
                        parsed->mac_src);
        break;
    case 6: /* abort */
        output_report_status(
                        out,
                        timestamp,
                        PortStatus_Closed,
                        ip_them,
                        132, /* ip proto = sctp */
                        port_them,
                        0,
                        parsed->ip_ttl,
                        parsed->mac_src);
        break;
    default:
        ;
    }



}