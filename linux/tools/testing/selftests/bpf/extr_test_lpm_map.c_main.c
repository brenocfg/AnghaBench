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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  test_lpm_basic () ; 
 int /*<<< orphan*/  test_lpm_delete () ; 
 int /*<<< orphan*/  test_lpm_get_next_key () ; 
 int /*<<< orphan*/  test_lpm_ipaddr () ; 
 int /*<<< orphan*/  test_lpm_map (int) ; 
 int /*<<< orphan*/  test_lpm_multi_thread () ; 
 int /*<<< orphan*/  test_lpm_order () ; 

int main(void)
{
	int i;

	/* we want predictable, pseudo random tests */
	srand(0xf00ba1);

	test_lpm_basic();
	test_lpm_order();

	/* Test with 8, 16, 24, 32, ... 128 bit prefix length */
	for (i = 1; i <= 16; ++i)
		test_lpm_map(i);

	test_lpm_ipaddr();
	test_lpm_delete();
	test_lpm_get_next_key();
	test_lpm_multi_thread();

	printf("test_lpm: OK\n");
	return 0;
}