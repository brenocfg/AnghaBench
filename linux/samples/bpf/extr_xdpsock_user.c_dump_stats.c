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
struct TYPE_2__ {int /*<<< orphan*/  tx_npkts; int /*<<< orphan*/  prev_tx_npkts; int /*<<< orphan*/  rx_npkts; int /*<<< orphan*/  prev_rx_npkts; } ;

/* Variables and functions */
 unsigned long get_nsecs () ; 
 int num_socks ; 
 unsigned long prev_time ; 
 int /*<<< orphan*/  print_benchmark (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__** xsks ; 

__attribute__((used)) static void dump_stats(void)
{
	unsigned long now = get_nsecs();
	long dt = now - prev_time;
	int i;

	prev_time = now;

	for (i = 0; i < num_socks && xsks[i]; i++) {
		char *fmt = "%-15s %'-11.0f %'-11lu\n";
		double rx_pps, tx_pps;

		rx_pps = (xsks[i]->rx_npkts - xsks[i]->prev_rx_npkts) *
			 1000000000. / dt;
		tx_pps = (xsks[i]->tx_npkts - xsks[i]->prev_tx_npkts) *
			 1000000000. / dt;

		printf("\n sock%d@", i);
		print_benchmark(false);
		printf("\n");

		printf("%-15s %-11s %-11s %-11.2f\n", "", "pps", "pkts",
		       dt / 1000000000.);
		printf(fmt, "rx", rx_pps, xsks[i]->rx_npkts);
		printf(fmt, "tx", tx_pps, xsks[i]->tx_npkts);

		xsks[i]->prev_rx_npkts = xsks[i]->rx_npkts;
		xsks[i]->prev_tx_npkts = xsks[i]->tx_npkts;
	}
}