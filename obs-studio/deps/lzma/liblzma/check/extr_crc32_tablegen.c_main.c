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
 int /*<<< orphan*/  init_crc32_table () ; 
 int /*<<< orphan*/  print_crc32_table () ; 
 int /*<<< orphan*/  print_lz_table () ; 

int
main(void)
{
	init_crc32_table();

#ifdef LZ_HASH_TABLE
	print_lz_table();
#else
	print_crc32_table();
#endif

	return 0;
}