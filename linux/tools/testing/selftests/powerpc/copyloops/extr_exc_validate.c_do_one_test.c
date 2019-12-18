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
 unsigned long COPY_LOOP (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long test_copy_tofrom_user_reference (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  total_failed ; 
 int /*<<< orphan*/  total_passed ; 

__attribute__((used)) static void do_one_test(char *dstp, char *srcp, unsigned long len)
{
	unsigned long got, expected;

	got = COPY_LOOP(dstp, srcp, len);
	expected = test_copy_tofrom_user_reference(dstp, srcp, len);

	if (got != expected) {
		total_failed++;
		printf("FAIL from=%p to=%p len=%ld returned %ld, expected %ld\n",
		       srcp, dstp, len, got, expected);
		//abort();
	} else
		total_passed++;
}