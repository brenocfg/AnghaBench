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
struct ceph_mds_request {int dummy; } ;
struct ceph_mds_client {int /*<<< orphan*/  request_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_mdsc_get_request (struct ceph_mds_request*) ; 
 struct ceph_mds_request* lookup_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_mds_request *
lookup_get_request(struct ceph_mds_client *mdsc, u64 tid)
{
	struct ceph_mds_request *req;

	req = lookup_request(&mdsc->request_tree, tid);
	if (req)
		ceph_mdsc_get_request(req);

	return req;
}