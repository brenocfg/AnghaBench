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
struct buffer_head {scalar_t__ b_assoc_map; TYPE_1__* b_page; } ;
struct TYPE_2__ {scalar_t__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  mapping_set_error (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_write_io_error (struct buffer_head*) ; 

void mark_buffer_write_io_error(struct buffer_head *bh)
{
	set_buffer_write_io_error(bh);
	/* FIXME: do we need to set this in both places? */
	if (bh->b_page && bh->b_page->mapping)
		mapping_set_error(bh->b_page->mapping, -EIO);
	if (bh->b_assoc_map)
		mapping_set_error(bh->b_assoc_map, -EIO);
}