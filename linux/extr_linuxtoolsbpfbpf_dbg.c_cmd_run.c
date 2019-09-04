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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct pcap_pkthdr {int /*<<< orphan*/  len; int /*<<< orphan*/  caplen; } ;

/* Variables and functions */
 int CMD_ERR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  bpf_image ; 
 int /*<<< orphan*/  bpf_prog_len ; 
 int /*<<< orphan*/  bpf_prog_loaded () ; 
 int /*<<< orphan*/  bpf_reset () ; 
 int bpf_run_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcap_pkthdr* pcap_curr_pkt () ; 
 int /*<<< orphan*/  pcap_loaded () ; 
 scalar_t__ pcap_next_pkt () ; 
 int /*<<< orphan*/  pcap_reset_pkt () ; 
 int /*<<< orphan*/  rl_printf (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmd_run(char *num)
{
	static uint32_t pass, fail;
	bool has_limit = true;
	int pkts = 0, i = 0;

	if (!bpf_prog_loaded() || !pcap_loaded())
		return CMD_ERR;

	pkts = strtol(num, NULL, 10);
	if (pkts == 0 || strlen(num) == 0)
		has_limit = false;

	do {
		struct pcap_pkthdr *hdr = pcap_curr_pkt();
		int ret = bpf_run_all(bpf_image, bpf_prog_len,
				      (uint8_t *) hdr + sizeof(*hdr),
				      hdr->caplen, hdr->len);
		if (ret > 0)
			pass++;
		else if (ret == 0)
			fail++;
		else
			return CMD_OK;
		bpf_reset();
	} while (pcap_next_pkt() && (!has_limit || (has_limit && ++i < pkts)));

	rl_printf("bpf passes:%u fails:%u\n", pass, fail);

	pcap_reset_pkt();
	bpf_reset();

	pass = fail = 0;
	return CMD_OK;
}