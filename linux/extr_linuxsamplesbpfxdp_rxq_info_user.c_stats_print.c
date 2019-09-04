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
struct datarec {int dummy; } ;
struct record {struct datarec total; struct datarec* cpu; } ;
struct stats_record {struct record* rxq; struct record stats; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {unsigned int max_entries; } ;

/* Variables and functions */
 char* action2str (int) ; 
 TYPE_1__* bpf_map__def (int /*<<< orphan*/ ) ; 
 unsigned int bpf_num_possible_cpus () ; 
 double calc_errs_pps (struct datarec*,struct datarec*,double) ; 
 double calc_period (struct record*,struct record*) ; 
 double calc_pps (struct datarec*,struct datarec*,double) ; 
 int ifindex ; 
 char* ifname ; 
 char* options2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  rx_queue_index_map ; 

__attribute__((used)) static void stats_print(struct stats_record *stats_rec,
			struct stats_record *stats_prev,
			int action, __u32 cfg_opt)
{
	unsigned int nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	unsigned int nr_cpus = bpf_num_possible_cpus();
	double pps = 0, err = 0;
	struct record *rec, *prev;
	double t;
	int rxq;
	int i;

	/* Header */
	printf("\nRunning XDP on dev:%s (ifindex:%d) action:%s options:%s\n",
	       ifname, ifindex, action2str(action), options2str(cfg_opt));

	/* stats_global_map */
	{
		char *fmt_rx = "%-15s %-7d %'-11.0f %'-10.0f %s\n";
		char *fm2_rx = "%-15s %-7s %'-11.0f\n";
		char *errstr = "";

		printf("%-15s %-7s %-11s %-11s\n",
		       "XDP stats", "CPU", "pps", "issue-pps");

		rec  =  &stats_rec->stats;
		prev = &stats_prev->stats;
		t = calc_period(rec, prev);
		for (i = 0; i < nr_cpus; i++) {
			struct datarec *r = &rec->cpu[i];
			struct datarec *p = &prev->cpu[i];

			pps = calc_pps     (r, p, t);
			err = calc_errs_pps(r, p, t);
			if (err > 0)
				errstr = "invalid-ifindex";
			if (pps > 0)
				printf(fmt_rx, "XDP-RX CPU",
					i, pps, err, errstr);
		}
		pps  = calc_pps     (&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		printf(fm2_rx, "XDP-RX CPU", "total", pps, err);
	}

	/* rx_queue_index_map */
	printf("\n%-15s %-7s %-11s %-11s\n",
	       "RXQ stats", "RXQ:CPU", "pps", "issue-pps");

	for (rxq = 0; rxq < nr_rxqs; rxq++) {
		char *fmt_rx = "%-15s %3d:%-3d %'-11.0f %'-10.0f %s\n";
		char *fm2_rx = "%-15s %3d:%-3s %'-11.0f\n";
		char *errstr = "";
		int rxq_ = rxq;

		/* Last RXQ in map catch overflows */
		if (rxq_ == nr_rxqs - 1)
			rxq_ = -1;

		rec  =  &stats_rec->rxq[rxq];
		prev = &stats_prev->rxq[rxq];
		t = calc_period(rec, prev);
		for (i = 0; i < nr_cpus; i++) {
			struct datarec *r = &rec->cpu[i];
			struct datarec *p = &prev->cpu[i];

			pps = calc_pps     (r, p, t);
			err = calc_errs_pps(r, p, t);
			if (err > 0) {
				if (rxq_ == -1)
					errstr = "map-overflow-RXQ";
				else
					errstr = "err";
			}
			if (pps > 0)
				printf(fmt_rx, "rx_queue_index",
				       rxq_, i, pps, err, errstr);
		}
		pps  = calc_pps     (&rec->total, &prev->total, t);
		err  = calc_errs_pps(&rec->total, &prev->total, t);
		if (pps || err)
			printf(fm2_rx, "rx_queue_index", rxq_, "sum", pps, err);
	}
}