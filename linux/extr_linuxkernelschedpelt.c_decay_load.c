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

/* Variables and functions */
 int LOAD_AVG_PERIOD ; 
 int mul_u64_u32_shr (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * runnable_avg_yN_inv ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 decay_load(u64 val, u64 n)
{
	unsigned int local_n;

	if (unlikely(n > LOAD_AVG_PERIOD * 63))
		return 0;

	/* after bounds checking we can collapse to 32-bit */
	local_n = n;

	/*
	 * As y^PERIOD = 1/2, we can combine
	 *    y^n = 1/2^(n/PERIOD) * y^(n%PERIOD)
	 * With a look-up table which covers y^n (n<PERIOD)
	 *
	 * To achieve constant time decay_load.
	 */
	if (unlikely(local_n >= LOAD_AVG_PERIOD)) {
		val >>= local_n / LOAD_AVG_PERIOD;
		local_n %= LOAD_AVG_PERIOD;
	}

	val = mul_u64_u32_shr(val, runnable_avg_yN_inv[local_n], 32);
	return val;
}