#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ceph_pagelist {scalar_t__ length; int /*<<< orphan*/  head; } ;
struct ceph_msg_data_cursor {scalar_t__ offset; scalar_t__ resid; int last_piece; TYPE_1__* page; struct ceph_msg_data* data; } ;
struct ceph_msg_data {scalar_t__ type; struct ceph_pagelist* pagelist; } ;
struct TYPE_3__ {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_MSG_DATA_PAGELIST ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SIZE ; 
 int list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru ; 

__attribute__((used)) static bool ceph_msg_data_pagelist_advance(struct ceph_msg_data_cursor *cursor,
						size_t bytes)
{
	struct ceph_msg_data *data = cursor->data;
	struct ceph_pagelist *pagelist;

	BUG_ON(data->type != CEPH_MSG_DATA_PAGELIST);

	pagelist = data->pagelist;
	BUG_ON(!pagelist);

	BUG_ON(cursor->offset + cursor->resid != pagelist->length);
	BUG_ON((cursor->offset & ~PAGE_MASK) + bytes > PAGE_SIZE);

	/* Advance the cursor offset */

	cursor->resid -= bytes;
	cursor->offset += bytes;
	/* offset of first page in pagelist is always 0 */
	if (!bytes || cursor->offset & ~PAGE_MASK)
		return false;	/* more bytes to process in the current page */

	if (!cursor->resid)
		return false;   /* no more data */

	/* Move on to the next page */

	BUG_ON(list_is_last(&cursor->page->lru, &pagelist->head));
	cursor->page = list_next_entry(cursor->page, lru);
	cursor->last_piece = cursor->resid <= PAGE_SIZE;

	return true;
}