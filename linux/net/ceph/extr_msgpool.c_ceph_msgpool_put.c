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
struct ceph_msgpool {int /*<<< orphan*/  pool; int /*<<< orphan*/  front_len; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  front_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  iov_len; } ;
struct ceph_msg {int /*<<< orphan*/  kref; scalar_t__ num_data_items; scalar_t__ data_length; TYPE_2__ hdr; TYPE_1__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_msg*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct ceph_msg*,int /*<<< orphan*/ ) ; 

void ceph_msgpool_put(struct ceph_msgpool *pool, struct ceph_msg *msg)
{
	dout("msgpool_put %s %p\n", pool->name, msg);

	/* reset msg front_len; user may have changed it */
	msg->front.iov_len = pool->front_len;
	msg->hdr.front_len = cpu_to_le32(pool->front_len);

	msg->data_length = 0;
	msg->num_data_items = 0;

	kref_init(&msg->kref);  /* retake single ref */
	mempool_free(msg, pool->pool);
}