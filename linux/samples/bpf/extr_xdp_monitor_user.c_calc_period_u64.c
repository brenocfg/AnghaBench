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
struct record_u64 {scalar_t__ timestamp; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 double NANOSEC_PER_SEC ; 

__attribute__((used)) static double calc_period_u64(struct record_u64 *r, struct record_u64 *p)
{
	double period_ = 0;
	__u64 period = 0;

	period = r->timestamp - p->timestamp;
	if (period > 0)
		period_ = ((double) period / NANOSEC_PER_SEC);

	return period_;
}