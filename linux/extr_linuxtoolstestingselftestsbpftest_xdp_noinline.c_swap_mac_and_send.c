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
struct eth_hdr {unsigned char* eth_source; unsigned char* eth_dest; } ;

/* Variables and functions */
 int XDP_TX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static __attribute__ ((noinline))
int swap_mac_and_send(void *data, void *data_end)
{
	unsigned char tmp_mac[6];
	struct eth_hdr *eth;

	eth = data;
	memcpy(tmp_mac, eth->eth_source, 6);
	memcpy(eth->eth_source, eth->eth_dest, 6);
	memcpy(eth->eth_dest, tmp_mac, 6);
	return XDP_TX;
}