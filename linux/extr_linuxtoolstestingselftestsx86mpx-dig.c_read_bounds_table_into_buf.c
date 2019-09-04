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

void *read_bounds_table_into_buf(unsigned long table_vaddr)
{
#ifdef MPX_DIG_STANDALONE
	static char bt_buf[MPX_BOUNDS_TABLE_SIZE_BYTES];
	off_t seek_ret = lseek(fd, table_vaddr, SEEK_SET);
	if (seek_ret != table_vaddr)
		mpx_dig_abort();

	int read_ret = read(fd, &bt_buf, sizeof(bt_buf));
	if (read_ret != sizeof(bt_buf))
		mpx_dig_abort();
	return &bt_buf;
#else
	return (void *)table_vaddr;
#endif
}