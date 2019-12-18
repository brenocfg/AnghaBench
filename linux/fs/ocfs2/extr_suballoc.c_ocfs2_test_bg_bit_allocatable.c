#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_group_desc {scalar_t__ bg_bitmap; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {scalar_t__ b_committed_data; } ;

/* Variables and functions */
 TYPE_1__* bh2jh (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 scalar_t__ ocfs2_test_bit (int,unsigned long*) ; 

__attribute__((used)) static int ocfs2_test_bg_bit_allocatable(struct buffer_head *bg_bh,
					 int nr)
{
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	int ret;

	if (ocfs2_test_bit(nr, (unsigned long *)bg->bg_bitmap))
		return 0;

	if (!buffer_jbd(bg_bh))
		return 1;

	jbd_lock_bh_state(bg_bh);
	bg = (struct ocfs2_group_desc *) bh2jh(bg_bh)->b_committed_data;
	if (bg)
		ret = !ocfs2_test_bit(nr, (unsigned long *)bg->bg_bitmap);
	else
		ret = 1;
	jbd_unlock_bh_state(bg_bh);

	return ret;
}