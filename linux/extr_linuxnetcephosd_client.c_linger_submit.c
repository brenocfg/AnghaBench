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
struct TYPE_2__ {int /*<<< orphan*/  osd; } ;
struct ceph_osd_linger_request {TYPE_1__ t; struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {int dummy; } ;
struct ceph_osd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_target (struct ceph_osd_client*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  link_linger (struct ceph_osd*,struct ceph_osd_linger_request*) ; 
 struct ceph_osd* lookup_create_osd (struct ceph_osd_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_linger (struct ceph_osd_linger_request*) ; 

__attribute__((used)) static void linger_submit(struct ceph_osd_linger_request *lreq)
{
	struct ceph_osd_client *osdc = lreq->osdc;
	struct ceph_osd *osd;

	calc_target(osdc, &lreq->t, NULL, false);
	osd = lookup_create_osd(osdc, lreq->t.osd, true);
	link_linger(osd, lreq);

	send_linger(lreq);
}