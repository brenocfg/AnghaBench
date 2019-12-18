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
struct ceph_msg_data_cursor {size_t total_resid; int need_crc; TYPE_1__* data; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  CEPH_MSG_DATA_BIO 132 
#define  CEPH_MSG_DATA_BVECS 131 
#define  CEPH_MSG_DATA_NONE 130 
#define  CEPH_MSG_DATA_PAGELIST 129 
#define  CEPH_MSG_DATA_PAGES 128 
 int /*<<< orphan*/  ceph_msg_data_bio_cursor_init (struct ceph_msg_data_cursor*,size_t) ; 
 int /*<<< orphan*/  ceph_msg_data_bvecs_cursor_init (struct ceph_msg_data_cursor*,size_t) ; 
 int /*<<< orphan*/  ceph_msg_data_pagelist_cursor_init (struct ceph_msg_data_cursor*,size_t) ; 
 int /*<<< orphan*/  ceph_msg_data_pages_cursor_init (struct ceph_msg_data_cursor*,size_t) ; 

__attribute__((used)) static void __ceph_msg_data_cursor_init(struct ceph_msg_data_cursor *cursor)
{
	size_t length = cursor->total_resid;

	switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		ceph_msg_data_pagelist_cursor_init(cursor, length);
		break;
	case CEPH_MSG_DATA_PAGES:
		ceph_msg_data_pages_cursor_init(cursor, length);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		ceph_msg_data_bio_cursor_init(cursor, length);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_BVECS:
		ceph_msg_data_bvecs_cursor_init(cursor, length);
		break;
	case CEPH_MSG_DATA_NONE:
	default:
		/* BUG(); */
		break;
	}
	cursor->need_crc = true;
}