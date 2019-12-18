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
typedef  void pcap_pkthdr ;

/* Variables and functions */
 scalar_t__ pcap_ptr_va_curr ; 

__attribute__((used)) static struct pcap_pkthdr *pcap_curr_pkt(void)
{
	return (void *) pcap_ptr_va_curr;
}