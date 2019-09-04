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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int __filemap_fdatawrite_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int filemap_check_errors (struct address_space*) ; 
 int filemap_fdatawait_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_needs_writeback (struct address_space*) ; 

int filemap_write_and_wait_range(struct address_space *mapping,
				 loff_t lstart, loff_t lend)
{
	int err = 0;

	if (mapping_needs_writeback(mapping)) {
		err = __filemap_fdatawrite_range(mapping, lstart, lend,
						 WB_SYNC_ALL);
		/* See comment of filemap_write_and_wait() */
		if (err != -EIO) {
			int err2 = filemap_fdatawait_range(mapping,
						lstart, lend);
			if (!err)
				err = err2;
		} else {
			/* Clear any previously stored errors */
			filemap_check_errors(mapping);
		}
	} else {
		err = filemap_check_errors(mapping);
	}
	return err;
}