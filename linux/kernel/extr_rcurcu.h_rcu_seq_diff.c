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
 unsigned long RCU_SEQ_CTR_SHIFT ; 
 unsigned long RCU_SEQ_STATE_MASK ; 
 scalar_t__ ULONG_CMP_GE (unsigned long,unsigned long) ; 

__attribute__((used)) static inline unsigned long rcu_seq_diff(unsigned long new, unsigned long old)
{
	unsigned long rnd_diff;

	if (old == new)
		return 0;
	/*
	 * Compute the number of grace periods (still shifted up), plus
	 * one if either of new and old is not an exact grace period.
	 */
	rnd_diff = (new & ~RCU_SEQ_STATE_MASK) -
		   ((old + RCU_SEQ_STATE_MASK) & ~RCU_SEQ_STATE_MASK) +
		   ((new & RCU_SEQ_STATE_MASK) || (old & RCU_SEQ_STATE_MASK));
	if (ULONG_CMP_GE(RCU_SEQ_STATE_MASK, rnd_diff))
		return 1; /* Definitely no grace period has elapsed. */
	return ((rnd_diff - RCU_SEQ_STATE_MASK - 1) >> RCU_SEQ_CTR_SHIFT) + 2;
}