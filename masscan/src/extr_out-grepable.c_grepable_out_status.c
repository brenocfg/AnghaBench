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
typedef  unsigned int time_t ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 char* name_from_ip_proto (unsigned int) ; 
 char* oproto_service_name (unsigned int) ; 
 char* status_string (int) ; 
 char* tcp_service_name (unsigned int) ; 
 char* udp_service_name (unsigned int) ; 

__attribute__((used)) static void
grepable_out_status(struct Output *out, FILE *fp, time_t timestamp,
    int status, unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    const char *service;
    UNUSEDPARM(timestamp);
    UNUSEDPARM(out);
    UNUSEDPARM(reason);
    UNUSEDPARM(ttl);

    if (ip_proto == 6)
        service = tcp_service_name(port);
    else if (ip_proto == 17)
        service = udp_service_name(port);
    else
        service = oproto_service_name(ip_proto);
    
    fprintf(fp, "Timestamp: %lu", timestamp);

    fprintf(fp, "\tHost: %u.%u.%u.%u ()",
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
                service, //service
                "", //SunRPC info
                "" //Version info
                );
}