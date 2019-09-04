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

__attribute__((used)) static inline unsigned long GET_BITS(unsigned long val, int bottombit, int topbit)
{
	int total_nr_bits = topbit - bottombit;
	unsigned long mask = (1UL << total_nr_bits)-1;
	return (val >> bottombit) & mask;
}