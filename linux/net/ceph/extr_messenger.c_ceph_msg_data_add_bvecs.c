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
struct ceph_msg_data {struct ceph_bvec_iter bvec_pos; int /*<<< orphan*/  type; } ;
struct ceph_msg {int /*<<< orphan*/  data_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MSG_DATA_BVECS ; 
 struct ceph_msg_data* ceph_msg_data_add (struct ceph_msg*) ; 

void ceph_msg_data_add_bvecs(struct ceph_msg *msg,
			     struct ceph_bvec_iter *bvec_pos)
{
	struct ceph_msg_data *data;

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_BVECS;
	data->bvec_pos = *bvec_pos;

	msg->data_length += bvec_pos->iter.bi_size;
}