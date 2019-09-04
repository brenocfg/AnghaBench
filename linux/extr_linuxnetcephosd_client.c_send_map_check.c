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
struct ceph_osd_request {int /*<<< orphan*/  r_tid; struct ceph_osd_client* r_osdc; } ;
struct ceph_osd_client {TYPE_1__* client; int /*<<< orphan*/  map_checks; } ;
struct TYPE_2__ {int /*<<< orphan*/  monc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ceph_monc_get_version_async (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_get_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  insert_request_mc (int /*<<< orphan*/ *,struct ceph_osd_request*) ; 
 struct ceph_osd_request* lookup_request_mc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_check_cb ; 
 int /*<<< orphan*/  verify_osdc_wrlocked (struct ceph_osd_client*) ; 

__attribute__((used)) static void send_map_check(struct ceph_osd_request *req)
{
	struct ceph_osd_client *osdc = req->r_osdc;
	struct ceph_osd_request *lookup_req;
	int ret;

	verify_osdc_wrlocked(osdc);

	lookup_req = lookup_request_mc(&osdc->map_checks, req->r_tid);
	if (lookup_req) {
		WARN_ON(lookup_req != req);
		return;
	}

	ceph_osdc_get_request(req);
	insert_request_mc(&osdc->map_checks, req);
	ret = ceph_monc_get_version_async(&osdc->client->monc, "osdmap",
					  map_check_cb, req->r_tid);
	WARN_ON(ret);
}