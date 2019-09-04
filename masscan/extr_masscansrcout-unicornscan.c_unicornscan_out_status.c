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
typedef  struct Output* time_t ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* name_from_ip_proto (unsigned int) ; 
 char* status_string (int) ; 
 char* tcp_service_name (unsigned int) ; 

__attribute__((used)) static void
unicornscan_out_status(struct Output *out, FILE *fp, time_t timestamp,
    int status, unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    UNUSEDPARM(reason);
    UNUSEDPARM(out);
    UNUSEDPARM(timestamp);

    if (ip_proto == 6) {
      fprintf(fp,"TCP %s\t%16s[%5d]\t\tfrom %u.%u.%u.%u  ttl %-3d\n",
              status_string(status),
              tcp_service_name(port),
              port,
              (ip>>24)&0xFF,
              (ip>>16)&0xFF,
              (ip>> 8)&0xFF,
              (ip>> 0)&0xFF,
              ttl);
    } else {
        /* unicornscan is TCP only, so just use grepable format for other protocols */
        fprintf(fp, "Host: %u.%u.%u.%u ()",
                (unsigned char)(ip>>24),
                (unsigned char)(ip>>16),
                (unsigned char)(ip>> 8),
                (unsigned char)(ip>> 0)
                );
        fprintf(fp, "\tPorts: %u/%s/%s/%s/%s/%s/%s\n",
                port,
                status_string(status),      //"open", "closed"
                name_from_ip_proto(ip_proto),  //"tcp", "udp", "sctp"
                "", //owner
                "", //service
                "", //SunRPC info
                "" //Version info
                );
    }
}