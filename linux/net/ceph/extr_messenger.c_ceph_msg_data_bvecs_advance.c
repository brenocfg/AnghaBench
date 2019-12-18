#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_8__ {scalar_t__ bi_bvec_done; } ;
struct ceph_msg_data_cursor {size_t resid; int last_piece; TYPE_3__ bvec_iter; TYPE_2__* data; } ;
struct bio_vec {int dummy; } ;
struct TYPE_6__ {struct bio_vec* bvecs; } ;
struct TYPE_7__ {TYPE_1__ bvec_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bvec_iter_advance (struct bio_vec*,TYPE_3__*,size_t) ; 
 size_t bvec_iter_len (struct bio_vec*,TYPE_3__) ; 
 struct page* bvec_iter_page (struct bio_vec*,TYPE_3__) ; 

__attribute__((used)) static bool ceph_msg_data_bvecs_advance(struct ceph_msg_data_cursor *cursor,
					size_t bytes)
{
	struct bio_vec *bvecs = cursor->data->bvec_pos.bvecs;
	struct page *page = bvec_iter_page(bvecs, cursor->bvec_iter);

	BUG_ON(bytes > cursor->resid);
	BUG_ON(bytes > bvec_iter_len(bvecs, cursor->bvec_iter));
	cursor->resid -= bytes;
	bvec_iter_advance(bvecs, &cursor->bvec_iter, bytes);

	if (!cursor->resid) {
		BUG_ON(!cursor->last_piece);
		return false;   /* no more data */
	}

	if (!bytes || (cursor->bvec_iter.bi_bvec_done &&
		       page == bvec_iter_page(bvecs, cursor->bvec_iter)))
		return false;	/* more bytes to process in this segment */

	BUG_ON(cursor->last_piece);
	BUG_ON(cursor->resid < bvec_iter_len(bvecs, cursor->bvec_iter));
	cursor->last_piece =
	    cursor->resid == bvec_iter_len(bvecs, cursor->bvec_iter);
	return true;
}