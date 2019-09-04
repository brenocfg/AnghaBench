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
struct buffer_head {int /*<<< orphan*/  b_state; struct buffer_head* b_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Shadow ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void journal_end_buffer_io_sync(struct buffer_head *bh, int uptodate)
{
	struct buffer_head *orig_bh = bh->b_private;

	BUFFER_TRACE(bh, "");
	if (uptodate)
		set_buffer_uptodate(bh);
	else
		clear_buffer_uptodate(bh);
	if (orig_bh) {
		clear_bit_unlock(BH_Shadow, &orig_bh->b_state);
		smp_mb__after_atomic();
		wake_up_bit(&orig_bh->b_state, BH_Shadow);
	}
	unlock_buffer(bh);
}