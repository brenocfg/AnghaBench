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
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  buf ; 
 int build_packet () ; 
 scalar_t__ cfg_expect_failure ; 
 int cfg_num_pkt ; 
 int cfg_num_secs ; 
 int /*<<< orphan*/  cfg_only_rx ; 
 int /*<<< orphan*/  cfg_only_tx ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_poll (int,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ do_rx (int) ; 
 scalar_t__ do_tx (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int setup_rx () ; 
 int setup_tx () ; 
 int /*<<< orphan*/  stderr ; 
 int util_gettime () ; 

__attribute__((used)) static int do_main(void)
{
	unsigned long tstop, treport, tcur;
	int fdt = -1, fdr = -1, len, tx = 0, rx = 0;

	if (!cfg_only_tx)
		fdr = setup_rx();
	if (!cfg_only_rx)
		fdt = setup_tx();

	len = build_packet();

	tcur = util_gettime();
	treport = tcur + 1000;
	tstop = tcur + (cfg_num_secs * 1000);

	while (1) {
		if (!cfg_only_rx)
			tx += do_tx(fdt, buf, len);

		if (!cfg_only_tx)
			rx += do_rx(fdr);

		if (cfg_num_secs) {
			tcur = util_gettime();
			if (tcur >= tstop)
				break;
			if (tcur >= treport) {
				fprintf(stderr, "pkts: tx=%u rx=%u\n", tx, rx);
				tx = 0;
				rx = 0;
				treport = tcur + 1000;
			}
		} else {
			if (tx == cfg_num_pkt)
				break;
		}
	}

	/* read straggler packets, if any */
	if (rx < tx) {
		tstop = util_gettime() + 100;
		while (rx < tx) {
			tcur = util_gettime();
			if (tcur >= tstop)
				break;

			do_poll(fdr, POLLIN, tstop - tcur);
			rx += do_rx(fdr);
		}
	}

	fprintf(stderr, "pkts: tx=%u rx=%u\n", tx, rx);

	if (fdr != -1 && close(fdr))
		error(1, errno, "close rx");
	if (fdt != -1 && close(fdt))
		error(1, errno, "close tx");

	/*
	 * success (== 0) only if received all packets
	 * unless failure is expected, in which case none must arrive.
	 */
	if (cfg_expect_failure)
		return rx != 0;
	else
		return rx != tx;
}