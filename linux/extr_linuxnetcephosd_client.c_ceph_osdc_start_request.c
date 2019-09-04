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
struct ceph_osd_request {int dummy; } ;
struct ceph_osd_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_request (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ceph_osdc_start_request(struct ceph_osd_client *osdc,
			    struct ceph_osd_request *req,
			    bool nofail)
{
	down_read(&osdc->lock);
	submit_request(req, false);
	up_read(&osdc->lock);

	return 0;
}