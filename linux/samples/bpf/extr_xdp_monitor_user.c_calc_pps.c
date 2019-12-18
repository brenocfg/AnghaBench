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
struct datarec {double processed; } ;
typedef  double __u64 ;

/* Variables and functions */

__attribute__((used)) static double calc_pps(struct datarec *r, struct datarec *p, double period)
{
	__u64 packets = 0;
	double pps = 0;

	if (period > 0) {
		packets = r->processed - p->processed;
		pps = packets / period;
	}
	return pps;
}