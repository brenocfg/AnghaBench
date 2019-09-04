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
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  pr_info (char*,char*,size_t) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_test_print_hex_dump(char *pre, const void *ptr, size_t len)
{
	/* limit the hex_dump */
	if (len < 1024) {
		print_hex_dump(KERN_INFO, pre,
			       DUMP_PREFIX_OFFSET, 16, 1,
			       ptr, len, 0);
		return;
	}
	/* print head */
	print_hex_dump(KERN_INFO, pre,
		       DUMP_PREFIX_OFFSET, 16, 1,
		       ptr, 512, 0);
	/* print tail */
	pr_info("%s truncated - continuing at offset %04zx\n",
		pre, len - 512);
	print_hex_dump(KERN_INFO, pre,
		       DUMP_PREFIX_OFFSET, 16, 1,
		       ptr + (len - 512), 512, 0);
}