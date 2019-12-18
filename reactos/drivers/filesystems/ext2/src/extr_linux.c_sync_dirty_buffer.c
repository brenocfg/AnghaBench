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
struct buffer_head {int /*<<< orphan*/  b_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  WRITE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int sync_dirty_buffer(struct buffer_head *bh)
{
    int ret = 0;

    ASSERT(atomic_read(&bh->b_count) <= 1);
    lock_buffer(bh);
    if (test_clear_buffer_dirty(bh)) {
        get_bh(bh);
        ret = submit_bh(WRITE, bh);
        wait_on_buffer(bh);
    } else {
        unlock_buffer(bh);
    }
    return ret;
}