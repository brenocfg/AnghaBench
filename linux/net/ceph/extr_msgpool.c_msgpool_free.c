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
struct ceph_msgpool {int /*<<< orphan*/  name; } ;
struct ceph_msg {int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_msg*) ; 

__attribute__((used)) static void msgpool_free(void *element, void *arg)
{
	struct ceph_msgpool *pool = arg;
	struct ceph_msg *msg = element;

	dout("msgpool_release %s %p\n", pool->name, msg);
	msg->pool = NULL;
	ceph_msg_put(msg);
}