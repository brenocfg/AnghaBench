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
struct ceph_osd_request {unsigned int r_num_ops; TYPE_1__* r_ops; } ;
struct ceph_osd_data {int dummy; } ;
struct TYPE_2__ {struct ceph_osd_data raw_data_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static struct ceph_osd_data *
osd_req_op_raw_data_in(struct ceph_osd_request *osd_req, unsigned int which)
{
	BUG_ON(which >= osd_req->r_num_ops);

	return &osd_req->r_ops[which].raw_data_in;
}