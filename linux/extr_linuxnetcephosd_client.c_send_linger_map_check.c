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
struct ceph_osd_linger_request {int /*<<< orphan*/  linger_id; struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {TYPE_1__* client; int /*<<< orphan*/  linger_map_checks; } ;
struct TYPE_2__ {int /*<<< orphan*/  monc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ceph_monc_get_version_async (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_linger_mc (int /*<<< orphan*/ *,struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_get (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_map_check_cb ; 
 struct ceph_osd_linger_request* lookup_linger_mc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_osdc_wrlocked (struct ceph_osd_client*) ; 

__attribute__((used)) static void send_linger_map_check(struct ceph_osd_linger_request *lreq)
{
	struct ceph_osd_client *osdc = lreq->osdc;
	struct ceph_osd_linger_request *lookup_lreq;
	int ret;

	verify_osdc_wrlocked(osdc);

	lookup_lreq = lookup_linger_mc(&osdc->linger_map_checks,
				       lreq->linger_id);
	if (lookup_lreq) {
		WARN_ON(lookup_lreq != lreq);
		return;
	}

	linger_get(lreq);
	insert_linger_mc(&osdc->linger_map_checks, lreq);
	ret = ceph_monc_get_version_async(&osdc->client->monc, "osdmap",
					  linger_map_check_cb, lreq->linger_id);
	WARN_ON(ret);
}