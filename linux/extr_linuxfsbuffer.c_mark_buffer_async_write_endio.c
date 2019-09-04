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
struct buffer_head {int /*<<< orphan*/ * b_end_io; } ;
typedef  int /*<<< orphan*/  bh_end_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_buffer_async_write (struct buffer_head*) ; 

__attribute__((used)) static void mark_buffer_async_write_endio(struct buffer_head *bh,
					  bh_end_io_t *handler)
{
	bh->b_end_io = handler;
	set_buffer_async_write(bh);
}