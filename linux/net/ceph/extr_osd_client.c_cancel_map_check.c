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
struct ceph_osd_request {int /*<<< orphan*/  r_tid; struct ceph_osd_client* r_osdc; } ;
struct ceph_osd_client {int /*<<< orphan*/  map_checks; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  erase_request_mc (int /*<<< orphan*/ *,struct ceph_osd_request*) ; 
 struct ceph_osd_request* lookup_request_mc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_osdc_wrlocked (struct ceph_osd_client*) ; 

__attribute__((used)) static void cancel_map_check(struct ceph_osd_request *req)
{
	struct ceph_osd_client *osdc = req->r_osdc;
	struct ceph_osd_request *lookup_req;

	verify_osdc_wrlocked(osdc);

	lookup_req = lookup_request_mc(&osdc->map_checks, req->r_tid);
	if (!lookup_req)
		return;

	WARN_ON(lookup_req != req);
	erase_request_mc(&osdc->map_checks, req);
	ceph_osdc_put_request(req);
}