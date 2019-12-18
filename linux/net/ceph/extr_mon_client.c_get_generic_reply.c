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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_msg_header {int /*<<< orphan*/  tid; } ;
struct ceph_msg {int dummy; } ;
struct ceph_mon_generic_request {int /*<<< orphan*/  reply; } ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; int /*<<< orphan*/  generic_request_tree; } ;
struct ceph_connection {struct ceph_mon_client* private; } ;

/* Variables and functions */
 struct ceph_msg* ceph_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ceph_mon_generic_request* lookup_generic_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ceph_msg *get_generic_reply(struct ceph_connection *con,
					 struct ceph_msg_header *hdr,
					 int *skip)
{
	struct ceph_mon_client *monc = con->private;
	struct ceph_mon_generic_request *req;
	u64 tid = le64_to_cpu(hdr->tid);
	struct ceph_msg *m;

	mutex_lock(&monc->mutex);
	req = lookup_generic_request(&monc->generic_request_tree, tid);
	if (!req) {
		dout("get_generic_reply %lld dne\n", tid);
		*skip = 1;
		m = NULL;
	} else {
		dout("get_generic_reply %lld got %p\n", tid, req->reply);
		*skip = 0;
		m = ceph_msg_get(req->reply);
		/*
		 * we don't need to track the connection reading into
		 * this reply because we only have one open connection
		 * at a time, ever.
		 */
	}
	mutex_unlock(&monc->mutex);
	return m;
}