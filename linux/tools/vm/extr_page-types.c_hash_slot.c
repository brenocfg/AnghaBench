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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t HASH_KEY (scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__* page_flags ; 

__attribute__((used)) static size_t hash_slot(uint64_t flags)
{
	size_t k = HASH_KEY(flags);
	size_t i;

	/* Explicitly reserve slot 0 for flags 0: the following logic
	 * cannot distinguish an unoccupied slot from slot (flags==0).
	 */
	if (flags == 0)
		return 0;

	/* search through the remaining (HASH_SIZE-1) slots */
	for (i = 1; i < ARRAY_SIZE(page_flags); i++, k++) {
		if (!k || k >= ARRAY_SIZE(page_flags))
			k = 1;
		if (page_flags[k] == 0) {
			page_flags[k] = flags;
			return k;
		}
		if (page_flags[k] == flags)
			return k;
	}

	fatal("hash table full: bump up HASH_SHIFT?\n");
	exit(EXIT_FAILURE);
}