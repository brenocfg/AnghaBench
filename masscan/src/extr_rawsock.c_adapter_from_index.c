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
typedef  int /*<<< orphan*/  pcap_if_t ;
struct TYPE_2__ {int (* findalldevs ) (int /*<<< orphan*/ **,char*) ;char const* (* dev_name ) (int /*<<< orphan*/  const*) ;int /*<<< orphan*/ * (* dev_next ) (int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 TYPE_1__ PCAP ; 
 int PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/  const*) ; 
 char const* stub3 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *
adapter_from_index(unsigned index)
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    int x;

    x = PCAP.findalldevs(&alldevs, errbuf);
    if (x != -1) {
        const pcap_if_t *d;

        if (alldevs == NULL) {
            fprintf(stderr, "ERR:libpcap: no adapters found, are you sure you are root?\n");
        }
        /* Print the list */
        for(d=alldevs; d; d=PCAP.dev_next(d)) {
            if (index-- == 0)
                return PCAP.dev_name(d);
        }
        return 0;
    } else {
        return 0;
    }
}