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
struct page {int dummy; } ;
struct ceph_msg_data_cursor {size_t resid; int last_piece; TYPE_1__* data; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  CEPH_MSG_DATA_BIO 132 
#define  CEPH_MSG_DATA_BVECS 131 
#define  CEPH_MSG_DATA_NONE 130 
#define  CEPH_MSG_DATA_PAGELIST 129 
#define  CEPH_MSG_DATA_PAGES 128 
 size_t PAGE_SIZE ; 
 struct page* ceph_msg_data_bio_next (struct ceph_msg_data_cursor*,size_t*,size_t*) ; 
 struct page* ceph_msg_data_bvecs_next (struct ceph_msg_data_cursor*,size_t*,size_t*) ; 
 struct page* ceph_msg_data_pagelist_next (struct ceph_msg_data_cursor*,size_t*,size_t*) ; 
 struct page* ceph_msg_data_pages_next (struct ceph_msg_data_cursor*,size_t*,size_t*) ; 

__attribute__((used)) static struct page *ceph_msg_data_next(struct ceph_msg_data_cursor *cursor,
					size_t *page_offset, size_t *length,
					bool *last_piece)
{
	struct page *page;

	switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		page = ceph_msg_data_pagelist_next(cursor, page_offset, length);
		break;
	case CEPH_MSG_DATA_PAGES:
		page = ceph_msg_data_pages_next(cursor, page_offset, length);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		page = ceph_msg_data_bio_next(cursor, page_offset, length);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_BVECS:
		page = ceph_msg_data_bvecs_next(cursor, page_offset, length);
		break;
	case CEPH_MSG_DATA_NONE:
	default:
		page = NULL;
		break;
	}

	BUG_ON(!page);
	BUG_ON(*page_offset + *length > PAGE_SIZE);
	BUG_ON(!*length);
	BUG_ON(*length > cursor->resid);
	if (last_piece)
		*last_piece = cursor->last_piece;

	return page;
}