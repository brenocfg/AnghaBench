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
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 int ktime_to_ns (int /*<<< orphan*/  const) ; 

s64 __ktime_divns(const ktime_t kt, s64 div)
{
	int sft = 0;
	s64 dclc;
	u64 tmp;

	dclc = ktime_to_ns(kt);
	tmp = dclc < 0 ? -dclc : dclc;

	/* Make sure the divisor is less than 2^32: */
	while (div >> 32) {
		sft++;
		div >>= 1;
	}
	tmp >>= sft;
	do_div(tmp, (unsigned long) div);
	return dclc < 0 ? -tmp : tmp;
}