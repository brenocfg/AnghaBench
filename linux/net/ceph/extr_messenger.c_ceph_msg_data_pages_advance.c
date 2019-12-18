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
struct ceph_msg_data_cursor {size_t page_offset; size_t resid; scalar_t__ page_index; scalar_t__ page_count; int last_piece; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_MSG_DATA_PAGES ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SIZE ; 

__attribute__((used)) static bool ceph_msg_data_pages_advance(struct ceph_msg_data_cursor *cursor,
						size_t bytes)
{
	BUG_ON(cursor->data->type != CEPH_MSG_DATA_PAGES);

	BUG_ON(cursor->page_offset + bytes > PAGE_SIZE);

	/* Advance the cursor page offset */

	cursor->resid -= bytes;
	cursor->page_offset = (cursor->page_offset + bytes) & ~PAGE_MASK;
	if (!bytes || cursor->page_offset)
		return false;	/* more bytes to process in the current page */

	if (!cursor->resid)
		return false;   /* no more data */

	/* Move on to the next page; offset is already at 0 */

	BUG_ON(cursor->page_index >= cursor->page_count);
	cursor->page_index++;
	cursor->last_piece = cursor->resid <= PAGE_SIZE;

	return true;
}