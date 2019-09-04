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
struct buffer_head {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_page_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_block_touch_buffer (struct buffer_head*) ; 

inline void touch_buffer(struct buffer_head *bh)
{
	trace_block_touch_buffer(bh);
	mark_page_accessed(bh->b_page);
}