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
struct pcap_pkthdr {scalar_t__ caplen; scalar_t__ len; } ;

/* Variables and functions */
 struct pcap_pkthdr* pcap_curr_pkt () ; 
 scalar_t__ pcap_map_size ; 
 scalar_t__ pcap_ptr_va_curr ; 
 scalar_t__ pcap_ptr_va_start ; 

__attribute__((used)) static bool pcap_next_pkt(void)
{
	struct pcap_pkthdr *hdr = pcap_curr_pkt();

	if (pcap_ptr_va_curr + sizeof(*hdr) -
	    pcap_ptr_va_start >= pcap_map_size)
		return false;
	if (hdr->caplen == 0 || hdr->len == 0 || hdr->caplen > hdr->len)
		return false;
	if (pcap_ptr_va_curr + sizeof(*hdr) + hdr->caplen -
	    pcap_ptr_va_start >= pcap_map_size)
		return false;

	pcap_ptr_va_curr += (sizeof(*hdr) + hdr->caplen);
	return true;
}