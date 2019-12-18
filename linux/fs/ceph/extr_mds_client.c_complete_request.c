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
struct ceph_mds_request {int /*<<< orphan*/  r_completion; int /*<<< orphan*/  (* r_callback ) (struct ceph_mds_client*,struct ceph_mds_request*) ;} ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ceph_mds_client*,struct ceph_mds_request*) ; 

__attribute__((used)) static void complete_request(struct ceph_mds_client *mdsc,
			     struct ceph_mds_request *req)
{
	if (req->r_callback)
		req->r_callback(mdsc, req);
	complete_all(&req->r_completion);
}