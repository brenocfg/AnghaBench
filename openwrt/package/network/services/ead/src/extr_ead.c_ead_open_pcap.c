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
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int PCAP_MRU ; 
 int /*<<< orphan*/  PCAP_TIMEOUT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_create (char const*,char*) ; 
 int /*<<< orphan*/  pcap_set_buffer_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcap_set_promisc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcap_set_protocol_linux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_set_snaplen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcap_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_recv_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static pcap_t *
ead_open_pcap(const char *ifname, char *errbuf, bool rx)
{
	pcap_t *p;

	p = pcap_create(ifname, errbuf);
	if (p == NULL)
		goto out;

	pcap_set_snaplen(p, PCAP_MRU);
	pcap_set_promisc(p, rx);
	pcap_set_timeout(p, PCAP_TIMEOUT);
	pcap_set_protocol_linux(p, (rx ? htons(ETH_P_IP) : 0));
	pcap_set_buffer_size(p, (rx ? 10 : 1) * PCAP_MRU);
	pcap_activate(p);
	set_recv_type(p, rx);
out:
	return p;
}