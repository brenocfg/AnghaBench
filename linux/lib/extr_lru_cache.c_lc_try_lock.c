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
struct lru_cache {unsigned long flags; } ;

/* Variables and functions */
 unsigned long LC_LOCKED ; 
 unsigned long LC_PARANOIA ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int lc_try_lock(struct lru_cache *lc)
{
	unsigned long val;
	do {
		val = cmpxchg(&lc->flags, 0, LC_LOCKED);
	} while (unlikely (val == LC_PARANOIA));
	/* Spin until no-one is inside a PARANOIA_ENTRY()/RETURN() section. */
	return 0 == val;
#if 0
	/* Alternative approach, spin in case someone enters or leaves a
	 * PARANOIA_ENTRY()/RETURN() section. */
	unsigned long old, new, val;
	do {
		old = lc->flags & LC_PARANOIA;
		new = old | LC_LOCKED;
		val = cmpxchg(&lc->flags, old, new);
	} while (unlikely (val == (old ^ LC_PARANOIA)));
	return old == val;
#endif
}