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
struct ceph_pagelist {scalar_t__ length; } ;
struct ceph_msg_data {int /*<<< orphan*/  links; struct ceph_pagelist* pagelist; } ;
struct ceph_msg {int /*<<< orphan*/  data_length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_MSG_DATA_PAGELIST ; 
 struct ceph_msg_data* ceph_msg_data_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ceph_msg_data_add_pagelist(struct ceph_msg *msg,
				struct ceph_pagelist *pagelist)
{
	struct ceph_msg_data *data;

	BUG_ON(!pagelist);
	BUG_ON(!pagelist->length);

	data = ceph_msg_data_create(CEPH_MSG_DATA_PAGELIST);
	BUG_ON(!data);
	data->pagelist = pagelist;

	list_add_tail(&data->links, &msg->data);
	msg->data_length += pagelist->length;
}