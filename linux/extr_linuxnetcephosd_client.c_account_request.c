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
struct ceph_osd_request {int r_flags; int /*<<< orphan*/  r_start_stamp; TYPE_1__* r_osdc; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_requests; } ;

/* Variables and functions */
 int CEPH_OSD_FLAG_ACK ; 
 int CEPH_OSD_FLAG_ONDISK ; 
 int CEPH_OSD_FLAG_READ ; 
 int CEPH_OSD_FLAG_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void account_request(struct ceph_osd_request *req)
{
	WARN_ON(req->r_flags & (CEPH_OSD_FLAG_ACK | CEPH_OSD_FLAG_ONDISK));
	WARN_ON(!(req->r_flags & (CEPH_OSD_FLAG_READ | CEPH_OSD_FLAG_WRITE)));

	req->r_flags |= CEPH_OSD_FLAG_ONDISK;
	atomic_inc(&req->r_osdc->num_requests);

	req->r_start_stamp = jiffies;
}