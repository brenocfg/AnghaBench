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
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct ceph_bvec_iter {TYPE_1__ iter; } ;
struct ceph_msg_data {int /*<<< orphan*/  links; struct ceph_bvec_iter bvec_pos; } ;
struct ceph_msg {int /*<<< orphan*/  data_length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_MSG_DATA_BVECS ; 
 struct ceph_msg_data* ceph_msg_data_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ceph_msg_data_add_bvecs(struct ceph_msg *msg,
			     struct ceph_bvec_iter *bvec_pos)
{
	struct ceph_msg_data *data;

	data = ceph_msg_data_create(CEPH_MSG_DATA_BVECS);
	BUG_ON(!data);
	data->bvec_pos = *bvec_pos;

	list_add_tail(&data->links, &msg->data);
	msg->data_length += bvec_pos->iter.bi_size;
}