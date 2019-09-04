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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_msg_data_cursor {int page_offset; unsigned short page_count; int last_piece; int /*<<< orphan*/  resid; scalar_t__ page_index; struct ceph_msg_data* data; } ;
struct ceph_msg_data {scalar_t__ type; int alignment; scalar_t__ length; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_MSG_DATA_PAGES ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 size_t SIZE_MAX ; 
 scalar_t__ USHRT_MAX ; 
 int calc_pages_for (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,scalar_t__) ; 

__attribute__((used)) static void ceph_msg_data_pages_cursor_init(struct ceph_msg_data_cursor *cursor,
					size_t length)
{
	struct ceph_msg_data *data = cursor->data;
	int page_count;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGES);

	BUG_ON(!data->pages);
	BUG_ON(!data->length);

	cursor->resid = min(length, data->length);
	page_count = calc_pages_for(data->alignment, (u64)data->length);
	cursor->page_offset = data->alignment & ~PAGE_MASK;
	cursor->page_index = 0;
	BUG_ON(page_count > (int)USHRT_MAX);
	cursor->page_count = (unsigned short)page_count;
	BUG_ON(length > SIZE_MAX - cursor->page_offset);
	cursor->last_piece = cursor->page_offset + cursor->resid <= PAGE_SIZE;
}