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
 int /*<<< orphan*/  bpf_reset_breakpoints () ; 
 int cmd_load_bpf (char*) ; 
 int cmd_load_pcap (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ matches (char*,char*) ; 
 int /*<<< orphan*/  rl_printf (char*) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int cmd_load(char *arg)
{
	char *subcmd, *cont = NULL, *tmp = strdup(arg);
	int ret = CMD_OK;

	subcmd = strtok_r(tmp, " ", &cont);
	if (subcmd == NULL)
		goto out;
	if (matches(subcmd, "bpf") == 0) {
		bpf_reset();
		bpf_reset_breakpoints();

		if (!cont)
			ret = CMD_ERR;
		else
			ret = cmd_load_bpf(cont);
	} else if (matches(subcmd, "pcap") == 0) {
		ret = cmd_load_pcap(cont);
	} else {
out:
		rl_printf("bpf <code>:  load bpf code\n");
		rl_printf("pcap <file>: load pcap file\n");
		ret = CMD_ERR;
	}

	free(tmp);
	return ret;
}