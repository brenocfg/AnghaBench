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
 unsigned long RCU_SEQ_STATE_MASK ; 
 int ULONG_CMP_LT (unsigned long,unsigned long) ; 

__attribute__((used)) static inline bool rcu_seq_new_gp(unsigned long old, unsigned long new)
{
	return ULONG_CMP_LT((old + RCU_SEQ_STATE_MASK) & ~RCU_SEQ_STATE_MASK,
			    new);
}