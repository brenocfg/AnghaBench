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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (unsigned long,unsigned long) ; 
 int rcu_seq_state (unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline void rcu_seq_start(unsigned long *sp)
{
	WRITE_ONCE(*sp, *sp + 1);
	smp_mb(); /* Ensure update-side operation after counter increment. */
	WARN_ON_ONCE(rcu_seq_state(*sp) != 1);
}