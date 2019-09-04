#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ refcount_t ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_try_cmpxchg_relaxed (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

bool refcount_add_not_zero_checked(unsigned int i, refcount_t *r)
{
	unsigned int new, val = atomic_read(&r->refs);

	do {
		if (!val)
			return false;

		if (unlikely(val == UINT_MAX))
			return true;

		new = val + i;
		if (new < val)
			new = UINT_MAX;

	} while (!atomic_try_cmpxchg_relaxed(&r->refs, &val, new));

	WARN_ONCE(new == UINT_MAX, "refcount_t: saturated; leaking memory.\n");

	return true;
}