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
struct ceph_options {int /*<<< orphan*/  mount_timeout; } ;
struct ceph_mds_request {int /*<<< orphan*/  r_wait; int /*<<< orphan*/  r_tid; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; int /*<<< orphan*/  safe_umount_waiters; TYPE_2__* fsc; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_options* options; } ;

/* Variables and functions */
 struct ceph_mds_request* __get_oldest_req (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  __unregister_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_requests(struct ceph_mds_client *mdsc)
{
	struct ceph_options *opts = mdsc->fsc->client->options;
	struct ceph_mds_request *req;

	mutex_lock(&mdsc->mutex);
	if (__get_oldest_req(mdsc)) {
		mutex_unlock(&mdsc->mutex);

		dout("wait_requests waiting for requests\n");
		wait_for_completion_timeout(&mdsc->safe_umount_waiters,
				    ceph_timeout_jiffies(opts->mount_timeout));

		/* tear down remaining requests */
		mutex_lock(&mdsc->mutex);
		while ((req = __get_oldest_req(mdsc))) {
			dout("wait_requests timed out on tid %llu\n",
			     req->r_tid);
			list_del_init(&req->r_wait);
			__unregister_request(mdsc, req);
		}
	}
	mutex_unlock(&mdsc->mutex);
	dout("wait_requests done\n");
}