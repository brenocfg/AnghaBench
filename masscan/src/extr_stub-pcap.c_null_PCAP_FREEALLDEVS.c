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
 int /*<<< orphan*/  UNUSEDPARM (int /*<<< orphan*/ *) ; 
 void pcap_freealldevs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void null_PCAP_FREEALLDEVS(pcap_if_t *alldevs)
{
#ifdef STATICPCAP
    return pcap_freealldevs(alldevs);
#endif
    UNUSEDPARM(alldevs);
    return;
}