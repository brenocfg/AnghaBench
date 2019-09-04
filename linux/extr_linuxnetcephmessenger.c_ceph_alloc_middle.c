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
struct TYPE_2__ {int /*<<< orphan*/  middle_len; int /*<<< orphan*/  type; } ;
struct ceph_msg {int middle; TYPE_1__ hdr; } ;
struct ceph_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int ceph_buffer_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_type_name (int) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_msg*,int,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_alloc_middle(struct ceph_connection *con, struct ceph_msg *msg)
{
	int type = le16_to_cpu(msg->hdr.type);
	int middle_len = le32_to_cpu(msg->hdr.middle_len);

	dout("alloc_middle %p type %d %s middle_len %d\n", msg, type,
	     ceph_msg_type_name(type), middle_len);
	BUG_ON(!middle_len);
	BUG_ON(msg->middle);

	msg->middle = ceph_buffer_new(middle_len, GFP_NOFS);
	if (!msg->middle)
		return -ENOMEM;
	return 0;
}