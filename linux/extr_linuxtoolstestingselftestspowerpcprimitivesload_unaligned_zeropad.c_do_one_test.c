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
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 unsigned long load_unaligned_zeropad (char*) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  protect_region () ; 
 int /*<<< orphan*/  unprotect_region () ; 

__attribute__((used)) static int do_one_test(char *p, int page_offset)
{
	unsigned long should;
	unsigned long got;

	FAIL_IF(unprotect_region());
	should = *(unsigned long *)p;
	FAIL_IF(protect_region());

	got = load_unaligned_zeropad(p);

	if (should != got) {
		printf("offset %u load_unaligned_zeropad returned 0x%lx, should be 0x%lx\n", page_offset, got, should);
		return 1;
	}

	return 0;
}