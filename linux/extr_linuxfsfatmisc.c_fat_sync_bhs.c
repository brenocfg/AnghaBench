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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  write_dirty_buffer (struct buffer_head*,int /*<<< orphan*/ ) ; 

int fat_sync_bhs(struct buffer_head **bhs, int nr_bhs)
{
	int i, err = 0;

	for (i = 0; i < nr_bhs; i++)
		write_dirty_buffer(bhs[i], 0);

	for (i = 0; i < nr_bhs; i++) {
		wait_on_buffer(bhs[i]);
		if (!err && !buffer_uptodate(bhs[i]))
			err = -EIO;
	}
	return err;
}