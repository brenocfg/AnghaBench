#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct pcap_pkthdr {int /*<<< orphan*/  len; int /*<<< orphan*/  caplen; } ;
struct TYPE_2__ {scalar_t__ Rs; } ;

/* Variables and functions */
 int CMD_ERR ; 
 int CMD_OK ; 
 TYPE_1__ bpf_curr ; 
 int /*<<< orphan*/  bpf_image ; 
 int /*<<< orphan*/  bpf_prog_len ; 
 int /*<<< orphan*/  bpf_prog_loaded () ; 
 int /*<<< orphan*/  bpf_reset () ; 
 int /*<<< orphan*/  bpf_restore_regs (int) ; 
 int bpf_run_stepping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pcap_pkthdr* pcap_curr_pkt () ; 
 int /*<<< orphan*/  pcap_loaded () ; 
 int /*<<< orphan*/  pcap_next_pkt () ; 
 int /*<<< orphan*/  pcap_reset_pkt () ; 
 int /*<<< orphan*/  rl_printf (char*) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmd_step(char *num)
{
	struct pcap_pkthdr *hdr;
	int steps, ret;

	if (!bpf_prog_loaded() || !pcap_loaded())
		return CMD_ERR;

	steps = strtol(num, NULL, 10);
	if (steps == 0 || strlen(num) == 0)
		steps = 1;
	if (steps < 0) {
		if (!bpf_restore_regs(steps))
			return CMD_ERR;
		steps = 1;
	}

	hdr = pcap_curr_pkt();
	ret = bpf_run_stepping(bpf_image, bpf_prog_len,
			       (uint8_t *) hdr + sizeof(*hdr),
			       hdr->caplen, hdr->len, steps);
	if (ret >= 0 || bpf_curr.Rs) {
		bpf_reset();
		if (!pcap_next_pkt()) {
			rl_printf("(going back to first packet)\n");
			pcap_reset_pkt();
		} else {
			rl_printf("(next packet)\n");
		}
	}

	return CMD_OK;
}