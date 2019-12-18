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
typedef  int /*<<< orphan*/  pcap_if_t ;

/* Variables and functions */
 int pcap_findalldevs (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  seterr (char*,char*) ; 

__attribute__((used)) static int null_PCAP_FINDALLDEVS(pcap_if_t **alldevs, char *errbuf)
{
#ifdef STATICPCAP
    return pcap_findalldevs(alldevs, errbuf);
#endif
    *alldevs = 0;
    seterr(errbuf, "libpcap not loaded");
    return -1;
}