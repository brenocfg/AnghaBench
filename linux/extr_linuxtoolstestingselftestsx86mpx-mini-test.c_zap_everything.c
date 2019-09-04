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
 scalar_t__ MPX_BOUNDS_TABLE_COVERS ; 
 int NR_MALLOCS ; 
 scalar_t__ alignment ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bounds_dir_ptr ; 
 int /*<<< orphan*/  dprintf1 (char*,long) ; 
 int /*<<< orphan*/  free_one_malloc (int) ; 
 long inspect_me (int /*<<< orphan*/ ) ; 
 scalar_t__ sz_alignment ; 
 int /*<<< orphan*/  test_failed () ; 

void zap_everything(void)
{
	long after_zap;
	long before_zap;
	int i;

	before_zap = inspect_me(bounds_dir_ptr);
	dprintf1("zapping everything start: %ld\n", before_zap);
	for (i = 0; i < NR_MALLOCS; i++)
		free_one_malloc(i);

	after_zap = inspect_me(bounds_dir_ptr);
	dprintf1("zapping everything done: %ld\n", after_zap);
	/*
	 * We only guarantee to empty the thing out if our allocations are
	 * exactly aligned on the boundaries of a boudns table.
	 */
	if ((alignment >= MPX_BOUNDS_TABLE_COVERS) &&
	    (sz_alignment >= MPX_BOUNDS_TABLE_COVERS)) {
		if (after_zap != 0)
			test_failed();

		assert(after_zap == 0);
	}
}