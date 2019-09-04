#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct ceph_msg_data_cursor {int /*<<< orphan*/  bvec_iter; TYPE_2__* data; } ;
struct bio_vec {size_t bv_offset; size_t bv_len; struct page* bv_page; } ;
struct TYPE_3__ {int /*<<< orphan*/  bvecs; } ;
struct TYPE_4__ {TYPE_1__ bvec_pos; } ;

/* Variables and functions */
 struct bio_vec bvec_iter_bvec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *ceph_msg_data_bvecs_next(struct ceph_msg_data_cursor *cursor,
						size_t *page_offset,
						size_t *length)
{
	struct bio_vec bv = bvec_iter_bvec(cursor->data->bvec_pos.bvecs,
					   cursor->bvec_iter);

	*page_offset = bv.bv_offset;
	*length = bv.bv_len;
	return bv.bv_page;
}