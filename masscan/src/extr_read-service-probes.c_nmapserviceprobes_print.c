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
struct ServiceVersionInfo {int type; scalar_t__ is_a; int /*<<< orphan*/  value; struct ServiceVersionInfo* next; } ;
struct ServiceProbeMatch {char* service; struct ServiceVersionInfo* versioninfo; scalar_t__ is_include_newlines; scalar_t__ is_case_insensitive; int /*<<< orphan*/  regex_length; int /*<<< orphan*/  regex; struct ServiceProbeMatch* next; } ;
struct NmapServiceProbeList {unsigned int count; struct NmapServiceProbe** list; int /*<<< orphan*/  exclude; } ;
struct NmapServiceProbe {int protocol; char* name; int rarity; int totalwaitms; int tcpwrappedms; struct ServiceProbeMatch* match; int /*<<< orphan*/  sslports; int /*<<< orphan*/  ports; int /*<<< orphan*/  hellolength; int /*<<< orphan*/  hellostring; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  SvcV_CpeName 135 
#define  SvcV_DeviceType 134 
#define  SvcV_Hostname 133 
#define  SvcV_Info 132 
#define  SvcV_OperatingSystem 131 
#define  SvcV_ProductName 130 
#define  SvcV_Unknown 129 
#define  SvcV_Version 128 
 int /*<<< orphan*/  Templ_TCP ; 
 int /*<<< orphan*/  Templ_UDP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  nmapserviceprobes_print_dstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  nmapserviceprobes_print_hello (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  nmapserviceprobes_print_ports (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
nmapserviceprobes_print(const struct NmapServiceProbeList *list, FILE *fp)
{
    unsigned i;
    if (list == NULL)
        return;
    
    nmapserviceprobes_print_ports(&list->exclude, fp, "Exclude", ~0);
    
    for (i=0; i<list->count; i++) {
        struct NmapServiceProbe *probe = list->list[i];
        struct ServiceProbeMatch *match;
        
        /* print the first part of the probe */
        fprintf(fp, "Probe %s %s q",
                (probe->protocol==6)?"TCP":"UDP",
                probe->name);
        
        /* preting the query/hello string */
        nmapserviceprobes_print_hello(fp, probe->hellostring, probe->hellolength, '|');
        
        fprintf(fp, "\n");
        if (probe->rarity)
            fprintf(fp, "rarity %u\n", probe->rarity);
        if (probe->totalwaitms)
            fprintf(fp, "totalwaitms %u\n", probe->totalwaitms);
        if (probe->tcpwrappedms)
            fprintf(fp, "tcpwrappedms %u\n", probe->tcpwrappedms);
        nmapserviceprobes_print_ports(&probe->ports, fp, "ports", (probe->protocol==6)?Templ_TCP:Templ_UDP);
        nmapserviceprobes_print_ports(&probe->sslports, fp, "sslports", (probe->protocol==6)?Templ_TCP:Templ_UDP);
        
        for (match=probe->match; match; match = match->next) {
            struct ServiceVersionInfo *vi;
            
            fprintf(fp, "match %s m", match->service);
            nmapserviceprobes_print_dstring(fp, match->regex, match->regex_length, '/');
            if (match->is_case_insensitive)
                fprintf(fp, "i");
            if (match->is_include_newlines)
                fprintf(fp, "s");
            fprintf(fp, " ");
            
            for (vi=match->versioninfo; vi; vi=vi->next) {
                const char *tag = "";
                switch (vi->type) {
                    case SvcV_Unknown:          tag = "u"; break;
                    case SvcV_ProductName:      tag = "p"; break;
                    case SvcV_Version:          tag = "v"; break;
                    case SvcV_Info:             tag = "i"; break;
                    case SvcV_Hostname:         tag = "h"; break;
                    case SvcV_OperatingSystem:  tag = "o"; break;
                    case SvcV_DeviceType:       tag = "e"; break;
                    case SvcV_CpeName:          tag = "cpe:"; break;
                }
                fprintf(fp, "%s", tag);
                nmapserviceprobes_print_dstring(fp, vi->value, strlen(vi->value), '/');
                if (vi->is_a)
                    fprintf(fp, "a");
                fprintf(fp, " ");
            }
            fprintf(fp, "\n");
        }
        
    }
}