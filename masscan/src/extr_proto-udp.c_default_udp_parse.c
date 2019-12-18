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
struct PreprocessedInfo {unsigned int port_src; int* ip_src; int /*<<< orphan*/  ip_ttl; } ;
struct Output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_NONE ; 
 int /*<<< orphan*/  UNUSEDPARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_report_banner (struct Output*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

unsigned
default_udp_parse(struct Output *out, time_t timestamp,
           const unsigned char *px, unsigned length,
           struct PreprocessedInfo *parsed,
           uint64_t entropy)
{
    unsigned ip_them;
    //unsigned ip_me;
    unsigned port_them = parsed->port_src;
    //unsigned port_me = parsed->port_dst;
    
    UNUSEDPARM(entropy);

    ip_them = parsed->ip_src[0]<<24 | parsed->ip_src[1]<<16 | parsed->ip_src[2]<< 8 | parsed->ip_src[3]<<0;
    //ip_me = parsed->ip_dst[0]<<24 | parsed->ip_dst[1]<<16 | parsed->ip_dst[2]<< 8 | parsed->ip_dst[3]<<0;

    if (length > 64)
        length = 64;
    
    output_report_banner(
                         out, timestamp,
                         ip_them, 17, port_them,
                         PROTO_NONE,
                         parsed->ip_ttl,
                         px, length);

    return 0;
}