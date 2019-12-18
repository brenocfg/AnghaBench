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
struct TYPE_2__ {char* pcap_payloads_filename; char* nmap_payloads_filename; char* nmap_service_probes_filename; int /*<<< orphan*/  probes; int /*<<< orphan*/ * udp; int /*<<< orphan*/ * oproto; } ;
struct Masscan {TYPE_1__ payloads; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  nmapserviceprobes_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmapserviceprobes_read_file (char const*) ; 
 int /*<<< orphan*/  payloads_read_pcap (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* payloads_udp_create () ; 
 int /*<<< orphan*/  payloads_udp_readfile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char const*) ; 

void
masscan_load_database_files(struct Masscan *masscan)
{
    const char *filename;
    
    /*
     * "pcap-payloads"
     */
    filename = masscan->payloads.pcap_payloads_filename;
    if (filename) {
        if (masscan->payloads.udp == NULL)
            masscan->payloads.udp = payloads_udp_create();
        if (masscan->payloads.oproto == NULL)
            masscan->payloads.oproto = payloads_udp_create();

        payloads_read_pcap(filename, masscan->payloads.udp, masscan->payloads.oproto);
    }

    /*
     * "nmap-payloads"
     */
    filename = masscan->payloads.nmap_payloads_filename;
    if (filename) {
        FILE *fp;
        int err;
        
        
        err = fopen_s(&fp, filename, "rt");
        if (err || fp == NULL) {
            perror(filename);
        } else {
            if (masscan->payloads.udp == NULL)
                masscan->payloads.udp = payloads_udp_create();
            
            payloads_udp_readfile(fp, filename, masscan->payloads.udp);
            
            fclose(fp);
        }
    }
    
    /*
     * "nmap-service-probes"
     */
    filename = masscan->payloads.nmap_service_probes_filename;
    if (filename) {
        if (masscan->payloads.probes)
            nmapserviceprobes_free(masscan->payloads.probes);
        
        masscan->payloads.probes = nmapserviceprobes_read_file(filename);
    }
}