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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool atomic_inc_below(atomic_t *v, int u)
{
	int c, old;
	c = atomic_read(v);
	for (;;) {
		if (unlikely(c >= u))
			return false;
		old = atomic_cmpxchg(v, c, c+1);
		if (likely(old == c))
			return true;
		c = old;
	}
}