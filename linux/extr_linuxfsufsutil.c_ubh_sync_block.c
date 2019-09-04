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
struct ufs_buffer_head {unsigned int count; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_on_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_dirty_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ubh_sync_block(struct ufs_buffer_head *ubh)
{
	if (ubh) {
		unsigned i;

		for (i = 0; i < ubh->count; i++)
			write_dirty_buffer(ubh->bh[i], 0);

		for (i = 0; i < ubh->count; i++)
			wait_on_buffer(ubh->bh[i]);
	}
}