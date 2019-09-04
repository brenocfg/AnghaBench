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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int pcap_fd ; 
 scalar_t__ pcap_map_size ; 
 scalar_t__ pcap_packet ; 
 int /*<<< orphan*/ * pcap_ptr_va_curr ; 
 int /*<<< orphan*/  pcap_ptr_va_start ; 

__attribute__((used)) static void try_close_pcap(void)
{
	if (pcap_fd >= 0) {
		munmap(pcap_ptr_va_start, pcap_map_size);
		close(pcap_fd);

		pcap_ptr_va_start = pcap_ptr_va_curr = NULL;
		pcap_map_size = 0;
		pcap_packet = 0;
		pcap_fd = -1;
	}
}