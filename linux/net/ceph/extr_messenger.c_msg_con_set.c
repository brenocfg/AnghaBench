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
struct ceph_msg {struct ceph_connection* con; } ;
struct ceph_connection {TYPE_1__* ops; } ;
struct TYPE_2__ {struct ceph_connection* (* get ) (struct ceph_connection*) ;int /*<<< orphan*/  (* put ) (struct ceph_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct ceph_connection*) ; 
 struct ceph_connection* stub2 (struct ceph_connection*) ; 

__attribute__((used)) static void msg_con_set(struct ceph_msg *msg, struct ceph_connection *con)
{
	if (msg->con)
		msg->con->ops->put(msg->con);

	msg->con = con ? con->ops->get(con) : NULL;
	BUG_ON(msg->con != con);
}