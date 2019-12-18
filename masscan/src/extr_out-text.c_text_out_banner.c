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
typedef  scalar_t__ time_t ;
struct Output {int dummy; } ;
typedef  enum ApplicationProtocol { ____Placeholder_ApplicationProtocol } ApplicationProtocol ;
typedef  int /*<<< orphan*/  banner_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char*,char*) ; 
 char* masscan_app_to_string (int) ; 
 char* name_from_ip_proto (unsigned int) ; 
 char* normalize_string (unsigned char const*,unsigned int,char*,int) ; 

__attribute__((used)) static void
text_out_banner(struct Output *out, FILE *fp, time_t timestamp,
        unsigned ip, unsigned ip_proto, unsigned port,
        enum ApplicationProtocol proto, unsigned ttl,
        const unsigned char *px, unsigned length)
{
    char banner_buffer[4096];


    UNUSEDPARM(out);
    UNUSEDPARM(ttl);

    fprintf(fp, "%s %s %u %u.%u.%u.%u %u %s %s\n",
        "banner",
        name_from_ip_proto(ip_proto),
        port,
        (ip>>24)&0xFF,
        (ip>>16)&0xFF,
        (ip>> 8)&0xFF,
        (ip>> 0)&0xFF,
        (unsigned)timestamp,
        masscan_app_to_string(proto),
        normalize_string(px, length, banner_buffer, sizeof(banner_buffer))
        );
}