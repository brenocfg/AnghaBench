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
struct rcu_segcblist {long len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (long,long) ; 
 long atomic_long_xchg (long*,long) ; 
 int /*<<< orphan*/  smp_mb () ; 

long rcu_segcblist_xchg_len(struct rcu_segcblist *rsclp, long v)
{
#ifdef CONFIG_RCU_NOCB_CPU
	return atomic_long_xchg(&rsclp->len, v);
#else
	long ret = rsclp->len;

	smp_mb(); /* Up to the caller! */
	WRITE_ONCE(rsclp->len, v);
	smp_mb(); /* Up to the caller! */
	return ret;
#endif
}