#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct Range {scalar_t__ begin; scalar_t__ end; } ;
struct TYPE_7__ {unsigned int count; struct Range* list; } ;
struct TYPE_6__ {unsigned int count; struct Range* list; } ;
struct Masscan {unsigned int echo_all; unsigned int nic_count; int http_user_agent; char* http_user_agent_length; TYPE_1__* http_headers; TYPE_3__ targets; TYPE_2__ ports; int /*<<< orphan*/ * echo; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set ) (struct Masscan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ name; } ;
struct TYPE_5__ {char* header_name; char* header_value_length; int /*<<< orphan*/  header_value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ Templ_ICMP_echo ; 
 scalar_t__ Templ_Oproto_first ; 
 scalar_t__ Templ_Oproto_last ; 
 scalar_t__ Templ_SCTP ; 
 scalar_t__ Templ_UDP ; 
 TYPE_4__* config_parameters ; 
 unsigned int count_cidr_bits (struct Range) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  masscan_echo_nic (struct Masscan*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ min (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct Masscan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
masscan_echo(struct Masscan *masscan, FILE *fp, unsigned is_echo_all)
{
    unsigned i;
    unsigned l = 0;
    
    /*
     * NEW:
     * Print all configuration parameters
     */
    masscan->echo = fp;
    masscan->echo_all = is_echo_all;
    for (i=0; config_parameters[i].name; i++) {
        config_parameters[i].set(masscan, 0, 0);
    }
    masscan->echo = 0;
    masscan->echo_all = 0;
    
    /*
     * OLD:
     * Things here below are the old way of echoing parameters.
     * TODO: cleanup this code, replacing with the new way.
     */
    if (masscan->nic_count == 0)
        masscan_echo_nic(masscan, fp, 0);
    else {
        for (i=0; i<masscan->nic_count; i++)
            masscan_echo_nic(masscan, fp, i);
    }
    
    
    /*
     * Targets
     */
    fprintf(fp, "# TARGET SELECTION (IP, PORTS, EXCLUDES)\n");
    fprintf(fp, "ports = ");
    /* Disable comma generation for the first element */
    l = 0;
    for (i=0; i<masscan->ports.count; i++) {
        struct Range range = masscan->ports.list[i];
        do {
            struct Range rrange = range;
            unsigned done = 0;
            if (l)
                fprintf(fp, ",");
            l = 1;
            if (rrange.begin >= Templ_ICMP_echo) {
                rrange.begin -= Templ_ICMP_echo;
                rrange.end -= Templ_ICMP_echo;
                fprintf(fp,"I:");
                done = 1;
            } else if (rrange.begin >= Templ_SCTP) {
                rrange.begin -= Templ_SCTP;
                rrange.end -= Templ_SCTP;
                fprintf(fp,"S:");
                range.begin = Templ_ICMP_echo;
            } else if (rrange.begin >= Templ_UDP) {
                rrange.begin -= Templ_UDP;
                rrange.end -= Templ_UDP;
                fprintf(fp,"U:");
                range.begin = Templ_SCTP;
            } else if (Templ_Oproto_first <= rrange.begin && rrange.begin <= Templ_Oproto_last) {
                rrange.begin -= Templ_Oproto_first;
                rrange.end -= Templ_Oproto_first;
                fprintf(fp, "O:");
                range.begin = Templ_Oproto_first;
            } else
                range.begin = Templ_UDP;
            rrange.end = min(rrange.end, 65535);
            if (rrange.begin == rrange.end)
                fprintf(fp, "%u", rrange.begin);
            else
                fprintf(fp, "%u-%u", rrange.begin, rrange.end);
            if (done)
                break;
        } while (range.begin <= range.end);
    }
    fprintf(fp, "\n");
    for (i=0; i<masscan->targets.count; i++) {
        struct Range range = masscan->targets.list[i];
        fprintf(fp, "range = ");
        fprintf(fp, "%u.%u.%u.%u",
                (range.begin>>24)&0xFF,
                (range.begin>>16)&0xFF,
                (range.begin>> 8)&0xFF,
                (range.begin>> 0)&0xFF
                );
        if (range.begin != range.end) {
            unsigned cidr_bits = count_cidr_bits(range);
            
            if (cidr_bits) {
                fprintf(fp, "/%u", cidr_bits);
            } else
                fprintf(fp, "-%u.%u.%u.%u",
                        (range.end>>24)&0xFF,
                        (range.end>>16)&0xFF,
                        (range.end>> 8)&0xFF,
                        (range.end>> 0)&0xFF
                        );
        }
        fprintf(fp, "\n");
    }
    
    fprintf(fp, "\n");
    if (masscan->http_user_agent)
        fprintf(    fp,
                "http-user-agent = %.*s\n",
                masscan->http_user_agent_length,
                masscan->http_user_agent);
    
    for (i=0; i<sizeof(masscan->http_headers)/sizeof(masscan->http_headers[0]); i++) {
        if (masscan->http_headers[i].header_name == 0)
            continue;
        fprintf(    fp,
                "http-header[%s] = %.*s\n",
                masscan->http_headers[i].header_name,
                masscan->http_headers[i].header_value_length,
                masscan->http_headers[i].header_value);
    }
    
    
    
    
    
}