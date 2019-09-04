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
struct page {int dummy; } ;
struct ceph_pagelist {scalar_t__ length; } ;
struct ceph_msg_data_cursor {scalar_t__ offset; scalar_t__ resid; struct page* page; scalar_t__ last_piece; struct ceph_msg_data* data; } ;
struct ceph_msg_data {scalar_t__ type; struct ceph_pagelist* pagelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_MSG_DATA_PAGELIST ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SIZE ; 

__attribute__((used)) static struct page *
ceph_msg_data_pagelist_next(struct ceph_msg_data_cursor *cursor,
				size_t *page_offset, size_t *length)
{
	struct ceph_msg_data *data = cursor->data;
	struct ceph_pagelist *pagelist;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGELIST);

	pagelist = data->pagelist;
	BUG_ON(!pagelist);

	BUG_ON(!cursor->page);
	BUG_ON(cursor->offset + cursor->resid != pagelist->length);

	/* offset of first page in pagelist is always 0 */
	*page_offset = cursor->offset & ~PAGE_MASK;
	if (cursor->last_piece)
		*length = cursor->resid;
	else
		*length = PAGE_SIZE - *page_offset;

	return cursor->page;
}