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
 int CMD_ERR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  bpf_reset () ; 
 int /*<<< orphan*/ * pcap_curr_pkt () ; 
 int /*<<< orphan*/  pcap_loaded () ; 
 int pcap_next_pkt () ; 
 int /*<<< orphan*/  pcap_reset_pkt () ; 
 int /*<<< orphan*/  rl_printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmd_select(char *num)
{
	unsigned int which, i;
	bool have_next = true;

	if (!pcap_loaded() || strlen(num) == 0)
		return CMD_ERR;

	which = strtoul(num, NULL, 10);
	if (which == 0) {
		rl_printf("packet count starts with 1, clamping!\n");
		which = 1;
	}

	pcap_reset_pkt();
	bpf_reset();

	for (i = 0; i < which && (have_next = pcap_next_pkt()); i++)
		/* noop */;
	if (!have_next || pcap_curr_pkt() == NULL) {
		rl_printf("no packet #%u available!\n", which);
		pcap_reset_pkt();
		return CMD_ERR;
	}

	return CMD_OK;
}