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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_bits (struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_check (int) ; 
 int find_next_and_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nr_cpumask_bits ; 

int cpumask_next_and(int n, const struct cpumask *src1p,
		     const struct cpumask *src2p)
{
	/* -1 is a legal arg here. */
	if (n != -1)
		cpumask_check(n);
	return find_next_and_bit(cpumask_bits(src1p), cpumask_bits(src2p),
		nr_cpumask_bits, n + 1);
}