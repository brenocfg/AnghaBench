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
 int /*<<< orphan*/  ead_pcap_reopen (int) ; 
 int /*<<< orphan*/  handle_packet ; 
 scalar_t__ pcap_dispatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_fp_rx ; 

__attribute__((used)) static void
ead_pktloop(void)
{
	while (1) {
		if (pcap_dispatch(pcap_fp_rx, 1, handle_packet, NULL) < 0) {
			ead_pcap_reopen(false);
			continue;
		}
	}
}