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
struct ceph_msg_data_cursor {size_t resid; int need_crc; TYPE_1__* data; int /*<<< orphan*/  data_head; int /*<<< orphan*/  last_piece; scalar_t__ total_resid; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  links; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  CEPH_MSG_DATA_BVECS 131 
#define  CEPH_MSG_DATA_NONE 130 
#define  CEPH_MSG_DATA_PAGELIST 129 
#define  CEPH_MSG_DATA_PAGES 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ceph_msg_data_cursor_init (struct ceph_msg_data_cursor*) ; 
 int ceph_msg_data_bvecs_advance (struct ceph_msg_data_cursor*,size_t) ; 
 int ceph_msg_data_pagelist_advance (struct ceph_msg_data_cursor*,size_t) ; 
 int ceph_msg_data_pages_advance (struct ceph_msg_data_cursor*,size_t) ; 
 int /*<<< orphan*/  links ; 
 int list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* list_next_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ceph_msg_data_advance(struct ceph_msg_data_cursor *cursor,
				  size_t bytes)
{
	bool new_piece;

	BUG_ON(bytes > cursor->resid);
	switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		new_piece = ceph_msg_data_pagelist_advance(cursor, bytes);
		break;
	case CEPH_MSG_DATA_PAGES:
		new_piece = ceph_msg_data_pages_advance(cursor, bytes);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		new_piece = ceph_msg_data_bio_advance(cursor, bytes);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_BVECS:
		new_piece = ceph_msg_data_bvecs_advance(cursor, bytes);
		break;
	case CEPH_MSG_DATA_NONE:
	default:
		BUG();
		break;
	}
	cursor->total_resid -= bytes;

	if (!cursor->resid && cursor->total_resid) {
		WARN_ON(!cursor->last_piece);
		BUG_ON(list_is_last(&cursor->data->links, cursor->data_head));
		cursor->data = list_next_entry(cursor->data, links);
		__ceph_msg_data_cursor_init(cursor);
		new_piece = true;
	}
	cursor->need_crc = new_piece;
}