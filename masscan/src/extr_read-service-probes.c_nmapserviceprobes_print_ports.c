#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct RangeList {unsigned int count; TYPE_1__* list; } ;
struct TYPE_2__ {int begin; int end; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  Templ_ARP 134 
#define  Templ_ICMP_echo 133 
#define  Templ_ICMP_timestamp 132 
#define  Templ_SCTP 131 
#define  Templ_TCP 130 
#define  Templ_UDP 129 
#define  Templ_VulnCheck 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
nmapserviceprobes_print_ports(const struct RangeList *ranges, FILE *fp, const char *prefix, int default_proto)
{
    unsigned i;
    
    /* don't print anything if no ports */
    if (ranges == NULL || ranges->count == 0)
        return;
    
    /* 'Exclude', 'ports', 'sslports' */
    fprintf(fp, "%s ", prefix);
    
    /* print all ports */
    for (i=0; i<ranges->count; i++) {
        int proto;
        int begin = ranges->list[i].begin;
        int end = ranges->list[i].end;
        
        if (Templ_TCP <= begin && begin < Templ_UDP)
            proto = Templ_TCP;
        else if (Templ_UDP <= begin && begin < Templ_SCTP)
            proto = Templ_UDP;
        else
            proto = Templ_SCTP;
        
        /* If UDP, shift down */
        begin -= proto;
        end -= proto;
        
        /* print comma between ports, but not for first port */
        if (i)
            fprintf(fp, ",");
        
        /* Print either one number for a single port, or two numbers for a range */
        if (default_proto != proto) {
            default_proto = proto;
            switch (proto) {
                case Templ_TCP: fprintf(fp, "T:"); break;
                case Templ_UDP: fprintf(fp, "U:"); break;
                case Templ_SCTP: fprintf(fp, "S"); break;
                case Templ_ICMP_echo: fprintf(fp, "e");  break;
                case Templ_ICMP_timestamp: fprintf(fp, "t");  break;
                case Templ_ARP: fprintf(fp, "A"); break;
                case Templ_VulnCheck: fprintf(fp, "v"); break;
            }
        }
        fprintf(fp, "%u", begin);
        if (end > begin)
            fprintf(fp, "-%u", end);
    }
    fprintf(fp, "\n");
}