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
struct ceph_msg {int /*<<< orphan*/  list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_msg_remove(struct ceph_msg *msg)
{
	list_del_init(&msg->list_head);

	ceph_msg_put(msg);
}