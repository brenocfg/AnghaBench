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
struct ceph_osd_client {int dummy; } ;

/* Variables and functions */
 int wait_request_timeout (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 

int ceph_osdc_wait_request(struct ceph_osd_client *osdc,
			   struct ceph_osd_request *req)
{
	return wait_request_timeout(req, 0);
}