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
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_open_sync (char*,int) ; 

__attribute__((used)) static void
test_open_syncs(void)
{
	printf(_("\nCompare open_sync with different write sizes:\n"));
	printf(_("(This is designed to compare the cost of writing 16kB in different write\n"
			 "open_sync sizes.)\n"));

	test_open_sync(_(" 1 * 16kB open_sync write"), 16);
	test_open_sync(_(" 2 *  8kB open_sync writes"), 8);
	test_open_sync(_(" 4 *  4kB open_sync writes"), 4);
	test_open_sync(_(" 8 *  2kB open_sync writes"), 2);
	test_open_sync(_("16 *  1kB open_sync writes"), 1);
}