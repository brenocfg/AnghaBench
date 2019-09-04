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
struct virtio_net_hdr {int dummy; } ;

/* Variables and functions */
 int DATA_LEN ; 
 int cfg_payload_len ; 
 int /*<<< orphan*/  cfg_use_vlan ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_rx (int,int,scalar_t__) ; 
 int do_tx () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int setup_rx () ; 
 int setup_sniffer () ; 
 scalar_t__ tbuf ; 

__attribute__((used)) static void run_test(void)
{
	int fdr, fds, total_len;

	fdr = setup_rx();
	fds = setup_sniffer();

	total_len = do_tx();

	/* BPF filter accepts only this length, vlan changes MAC */
	if (cfg_payload_len == DATA_LEN && !cfg_use_vlan)
		do_rx(fds, total_len - sizeof(struct virtio_net_hdr),
		      tbuf + sizeof(struct virtio_net_hdr));

	do_rx(fdr, cfg_payload_len, tbuf + total_len - cfg_payload_len);

	if (close(fds))
		error(1, errno, "close s");
	if (close(fdr))
		error(1, errno, "close r");
}