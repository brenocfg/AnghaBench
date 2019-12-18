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
 int /*<<< orphan*/  atomic_try_cmpxchg_release (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

bool refcount_dec_not_one(refcount_t *r)
{
	unsigned int new, val = atomic_read(&r->refs);

	do {
		if (unlikely(val == UINT_MAX))
			return true;

		if (val == 1)
			return false;

		new = val - 1;
		if (new > val) {
			WARN_ONCE(new > val, "refcount_t: underflow; use-after-free.\n");
			return true;
		}

	} while (!atomic_try_cmpxchg_release(&r->refs, &val, new));

	return true;
}