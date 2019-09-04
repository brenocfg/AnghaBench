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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_clear_cow_buffer(handle_t *handle, struct buffer_head *bh)
{
	BUG_ON(buffer_dirty(bh));

	clear_buffer_mapped(bh);

	return 0;
}