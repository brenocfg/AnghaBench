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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_meta (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_prio (struct buffer_head*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static int write_end_fn(handle_t *handle, struct buffer_head *bh)
{
	int ret;
	if (!buffer_mapped(bh) || buffer_freed(bh))
		return 0;
	set_buffer_uptodate(bh);
	ret = ext4_handle_dirty_metadata(handle, NULL, bh);
	clear_buffer_meta(bh);
	clear_buffer_prio(bh);
	return ret;
}