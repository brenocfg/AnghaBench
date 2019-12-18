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
struct inode {int dummy; } ;
struct ceph_mds_request {int dummy; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int ceph_mdsc_submit_request (struct ceph_mds_client*,struct inode*,struct ceph_mds_request*) ; 
 int ceph_mdsc_wait_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_request*,...) ; 

int ceph_mdsc_do_request(struct ceph_mds_client *mdsc,
			 struct inode *dir,
			 struct ceph_mds_request *req)
{
	int err;

	dout("do_request on %p\n", req);

	/* issue */
	err = ceph_mdsc_submit_request(mdsc, dir, req);
	if (!err)
		err = ceph_mdsc_wait_request(mdsc, req);
	dout("do_request %p done, result %d\n", req, err);
	return err;
}