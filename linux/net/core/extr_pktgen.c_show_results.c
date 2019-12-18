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
struct pktgen_dev {char* result; int sofar; int cur_pkt_size; scalar_t__ errors; int /*<<< orphan*/  idle_acc; int /*<<< orphan*/  started_at; int /*<<< orphan*/  stopped_at; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int __u64 ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int div64_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long,unsigned long long,unsigned long long,unsigned long long,...) ; 

__attribute__((used)) static void show_results(struct pktgen_dev *pkt_dev, int nr_frags)
{
	__u64 bps, mbps, pps;
	char *p = pkt_dev->result;
	ktime_t elapsed = ktime_sub(pkt_dev->stopped_at,
				    pkt_dev->started_at);
	ktime_t idle = ns_to_ktime(pkt_dev->idle_acc);

	p += sprintf(p, "OK: %llu(c%llu+d%llu) usec, %llu (%dbyte,%dfrags)\n",
		     (unsigned long long)ktime_to_us(elapsed),
		     (unsigned long long)ktime_to_us(ktime_sub(elapsed, idle)),
		     (unsigned long long)ktime_to_us(idle),
		     (unsigned long long)pkt_dev->sofar,
		     pkt_dev->cur_pkt_size, nr_frags);

	pps = div64_u64(pkt_dev->sofar * NSEC_PER_SEC,
			ktime_to_ns(elapsed));

	bps = pps * 8 * pkt_dev->cur_pkt_size;

	mbps = bps;
	do_div(mbps, 1000000);
	p += sprintf(p, "  %llupps %lluMb/sec (%llubps) errors: %llu",
		     (unsigned long long)pps,
		     (unsigned long long)mbps,
		     (unsigned long long)bps,
		     (unsigned long long)pkt_dev->errors);
}