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
 scalar_t__ pcap_fd ; 
 int /*<<< orphan*/  rl_printf (char*) ; 

__attribute__((used)) static bool pcap_loaded(void)
{
	if (pcap_fd < 0)
		rl_printf("no pcap file loaded!\n");

	return pcap_fd >= 0;
}