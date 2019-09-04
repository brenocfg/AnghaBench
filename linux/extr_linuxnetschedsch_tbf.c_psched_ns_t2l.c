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
typedef  int u64 ;
struct psched_ratecfg {int rate_bytes_ps; scalar_t__ linklayer; int overhead; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 scalar_t__ TC_LINKLAYER_ATM ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 psched_ns_t2l(const struct psched_ratecfg *r,
			 u64 time_in_ns)
{
	/* The formula is :
	 * len = (time_in_ns * r->rate_bytes_ps) / NSEC_PER_SEC
	 */
	u64 len = time_in_ns * r->rate_bytes_ps;

	do_div(len, NSEC_PER_SEC);

	if (unlikely(r->linklayer == TC_LINKLAYER_ATM)) {
		do_div(len, 53);
		len = len * 48;
	}

	if (len > r->overhead)
		len -= r->overhead;
	else
		len = 0;

	return len;
}