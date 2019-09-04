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
 int /*<<< orphan*/  __multiorder_tag_test (int,int) ; 
 int /*<<< orphan*/  __multiorder_tag_test2 (int,int) ; 

__attribute__((used)) static void multiorder_tag_tests(void)
{
	int i, j;

	/* test multi-order entry for indices 0-7 with no sibling pointers */
	__multiorder_tag_test(0, 3);
	__multiorder_tag_test(5, 3);

	/* test multi-order entry for indices 8-15 with no sibling pointers */
	__multiorder_tag_test(8, 3);
	__multiorder_tag_test(15, 3);

	/*
	 * Our order 5 entry covers indices 0-31 in a tree with height=2.
	 * This is broken up as follows:
	 * 0-7:		canonical entry
	 * 8-15:	sibling 1
	 * 16-23:	sibling 2
	 * 24-31:	sibling 3
	 */
	__multiorder_tag_test(0, 5);
	__multiorder_tag_test(29, 5);

	/* same test, but with indices 32-63 */
	__multiorder_tag_test(32, 5);
	__multiorder_tag_test(44, 5);

	/*
	 * Our order 8 entry covers indices 0-255 in a tree with height=3.
	 * This is broken up as follows:
	 * 0-63:	canonical entry
	 * 64-127:	sibling 1
	 * 128-191:	sibling 2
	 * 192-255:	sibling 3
	 */
	__multiorder_tag_test(0, 8);
	__multiorder_tag_test(190, 8);

	/* same test, but with indices 256-511 */
	__multiorder_tag_test(256, 8);
	__multiorder_tag_test(300, 8);

	__multiorder_tag_test(0x12345678UL, 8);

	for (i = 1; i < 10; i++)
		for (j = 0; j < (10 << i); j++)
			__multiorder_tag_test2(i, j);
}