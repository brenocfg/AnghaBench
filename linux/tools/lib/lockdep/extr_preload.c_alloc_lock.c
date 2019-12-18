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
struct lock_lookup {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lock_lookup*) ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 scalar_t__ __init_state ; 
 struct lock_lookup* __locks ; 
 int /*<<< orphan*/  __locks_nr ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct lock_lookup* malloc (int) ; 

__attribute__((used)) static struct lock_lookup *alloc_lock(void)
{
	if (__init_state != done) {
		/*
		 * Some programs attempt to initialize and use locks in their
		 * allocation path. This means that a call to malloc() would
		 * result in locks being initialized and locked.
		 *
		 * Why is it an issue for us? dlsym() below will try allocating
		 * to give us the original function. Since this allocation will
		 * result in a locking operations, we have to let pthread deal
		 * with it, but we can't! we don't have the pointer to the
		 * original API since we're inside dlsym() trying to get it
		 */

		int idx = __locks_nr++;
		if (idx >= ARRAY_SIZE(__locks)) {
			dprintf(STDERR_FILENO,
		"LOCKDEP error: insufficient LIBLOCKDEP_STATIC_ENTRIES\n");
			exit(EX_UNAVAILABLE);
		}
		return __locks + idx;
	}

	return malloc(sizeof(struct lock_lookup));
}