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
struct ceph_osd_linger_request {int /*<<< orphan*/  linger_id; struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {int /*<<< orphan*/  linger_map_checks; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  erase_linger_mc (int /*<<< orphan*/ *,struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_put (struct ceph_osd_linger_request*) ; 
 struct ceph_osd_linger_request* lookup_linger_mc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_osdc_wrlocked (struct ceph_osd_client*) ; 

__attribute__((used)) static void cancel_linger_map_check(struct ceph_osd_linger_request *lreq)
{
	struct ceph_osd_client *osdc = lreq->osdc;
	struct ceph_osd_linger_request *lookup_lreq;

	verify_osdc_wrlocked(osdc);

	lookup_lreq = lookup_linger_mc(&osdc->linger_map_checks,
				       lreq->linger_id);
	if (!lookup_lreq)
		return;

	WARN_ON(lookup_lreq != lreq);
	erase_linger_mc(&osdc->linger_map_checks, lreq);
	linger_put(lreq);
}