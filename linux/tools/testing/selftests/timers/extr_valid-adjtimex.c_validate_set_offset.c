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
 int NSEC_PER_SEC ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ set_bad_offset (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ set_offset (int,int) ; 
 int /*<<< orphan*/  stdout ; 

int validate_set_offset(void)
{
	printf("Testing ADJ_SETOFFSET... ");
	fflush(stdout);

	/* Test valid values */
	if (set_offset(NSEC_PER_SEC - 1, 1))
		return -1;

	if (set_offset(-NSEC_PER_SEC + 1, 1))
		return -1;

	if (set_offset(-NSEC_PER_SEC - 1, 1))
		return -1;

	if (set_offset(5 * NSEC_PER_SEC, 1))
		return -1;

	if (set_offset(-5 * NSEC_PER_SEC, 1))
		return -1;

	if (set_offset(5 * NSEC_PER_SEC + NSEC_PER_SEC / 2, 1))
		return -1;

	if (set_offset(-5 * NSEC_PER_SEC - NSEC_PER_SEC / 2, 1))
		return -1;

	if (set_offset(USEC_PER_SEC - 1, 0))
		return -1;

	if (set_offset(-USEC_PER_SEC + 1, 0))
		return -1;

	if (set_offset(-USEC_PER_SEC - 1, 0))
		return -1;

	if (set_offset(5 * USEC_PER_SEC, 0))
		return -1;

	if (set_offset(-5 * USEC_PER_SEC, 0))
		return -1;

	if (set_offset(5 * USEC_PER_SEC + USEC_PER_SEC / 2, 0))
		return -1;

	if (set_offset(-5 * USEC_PER_SEC - USEC_PER_SEC / 2, 0))
		return -1;

	/* Test invalid values */
	if (set_bad_offset(0, -1, 1))
		return -1;
	if (set_bad_offset(0, -1, 0))
		return -1;
	if (set_bad_offset(0, 2 * NSEC_PER_SEC, 1))
		return -1;
	if (set_bad_offset(0, 2 * USEC_PER_SEC, 0))
		return -1;
	if (set_bad_offset(0, NSEC_PER_SEC, 1))
		return -1;
	if (set_bad_offset(0, USEC_PER_SEC, 0))
		return -1;
	if (set_bad_offset(0, -NSEC_PER_SEC, 1))
		return -1;
	if (set_bad_offset(0, -USEC_PER_SEC, 0))
		return -1;

	printf("[OK]\n");
	return 0;
}