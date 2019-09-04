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
struct ceph_mds_request {int dummy; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __do_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __register_request (struct ceph_mds_client*,struct ceph_mds_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ceph_mdsc_submit_request(struct ceph_mds_client *mdsc,
			      struct ceph_mds_request *req)
{
	dout("submit_request on %p\n", req);
	mutex_lock(&mdsc->mutex);
	__register_request(mdsc, req, NULL);
	__do_request(mdsc, req);
	mutex_unlock(&mdsc->mutex);
}