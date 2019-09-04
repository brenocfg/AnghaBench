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
struct netcp_intf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netcp_process_one_rx_packet (struct netcp_intf*) ; 

__attribute__((used)) static int netcp_process_rx_packets(struct netcp_intf *netcp,
				    unsigned int budget)
{
	int i;

	for (i = 0; (i < budget) && !netcp_process_one_rx_packet(netcp); i++)
		;
	return i;
}