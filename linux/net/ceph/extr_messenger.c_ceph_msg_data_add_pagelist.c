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
struct ceph_pagelist {scalar_t__ length; int /*<<< orphan*/  refcnt; } ;
struct ceph_msg_data {struct ceph_pagelist* pagelist; int /*<<< orphan*/  type; } ;
struct ceph_msg {int /*<<< orphan*/  data_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_MSG_DATA_PAGELIST ; 
 struct ceph_msg_data* ceph_msg_data_add (struct ceph_msg*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

void ceph_msg_data_add_pagelist(struct ceph_msg *msg,
				struct ceph_pagelist *pagelist)
{
	struct ceph_msg_data *data;

	BUG_ON(!pagelist);
	BUG_ON(!pagelist->length);

	data = ceph_msg_data_add(msg);
	data->type = CEPH_MSG_DATA_PAGELIST;
	refcount_inc(&pagelist->refcnt);
	data->pagelist = pagelist;

	msg->data_length += pagelist->length;
}