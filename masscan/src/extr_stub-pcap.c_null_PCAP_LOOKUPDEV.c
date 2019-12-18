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

/* Variables and functions */
 char* pcap_lookupdev (char*) ; 
 int /*<<< orphan*/  seterr (char*,char*) ; 

__attribute__((used)) static char *null_PCAP_LOOKUPDEV(char *errbuf)
{
#ifdef STATICPCAP
    return pcap_lookupdev(errbuf);
#endif
    seterr(errbuf, "libpcap not loaded");
    return "";
}