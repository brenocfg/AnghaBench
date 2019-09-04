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
struct ceph_msgpool {int front_len; int /*<<< orphan*/  name; int /*<<< orphan*/  pool; int /*<<< orphan*/  type; } ;
struct ceph_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ceph_msg* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int,...) ; 
 struct ceph_msg* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ceph_msg *ceph_msgpool_get(struct ceph_msgpool *pool,
				  int front_len)
{
	struct ceph_msg *msg;

	if (front_len > pool->front_len) {
		dout("msgpool_get %s need front %d, pool size is %d\n",
		       pool->name, front_len, pool->front_len);
		WARN_ON(1);

		/* try to alloc a fresh message */
		return ceph_msg_new(pool->type, front_len, GFP_NOFS, false);
	}

	msg = mempool_alloc(pool->pool, GFP_NOFS);
	dout("msgpool_get %s %p\n", pool->name, msg);
	return msg;
}