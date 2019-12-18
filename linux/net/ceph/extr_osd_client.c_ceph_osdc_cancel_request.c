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
struct ceph_osd_request {scalar_t__ r_osd; struct ceph_osd_client* r_osdc; } ;
struct ceph_osd_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ceph_osdc_cancel_request(struct ceph_osd_request *req)
{
	struct ceph_osd_client *osdc = req->r_osdc;

	down_write(&osdc->lock);
	if (req->r_osd)
		cancel_request(req);
	up_write(&osdc->lock);
}