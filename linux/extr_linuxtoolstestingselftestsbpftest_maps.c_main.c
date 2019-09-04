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
 scalar_t__ BPF_F_NO_PREALLOC ; 
 scalar_t__ map_flags ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_all_tests () ; 

int main(void)
{
	map_flags = 0;
	run_all_tests();

	map_flags = BPF_F_NO_PREALLOC;
	run_all_tests();

	printf("test_maps: OK\n");
	return 0;
}