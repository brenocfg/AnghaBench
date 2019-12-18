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
struct ceph_osd_linger_request {struct ceph_osd* osd; TYPE_1__ t; struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {int dummy; } ;
struct ceph_osd {int dummy; } ;
typedef  enum calc_target_result { ____Placeholder_calc_target_result } calc_target_result ;

/* Variables and functions */
 int CALC_TARGET_NEED_RESEND ; 
 int calc_target (struct ceph_osd_client*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  link_linger (struct ceph_osd*,struct ceph_osd_linger_request*) ; 
 struct ceph_osd* lookup_create_osd (struct ceph_osd_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink_linger (struct ceph_osd*,struct ceph_osd_linger_request*) ; 

__attribute__((used)) static enum calc_target_result
recalc_linger_target(struct ceph_osd_linger_request *lreq)
{
	struct ceph_osd_client *osdc = lreq->osdc;
	enum calc_target_result ct_res;

	ct_res = calc_target(osdc, &lreq->t, true);
	if (ct_res == CALC_TARGET_NEED_RESEND) {
		struct ceph_osd *osd;

		osd = lookup_create_osd(osdc, lreq->t.osd, true);
		if (osd != lreq->osd) {
			unlink_linger(lreq->osd, lreq);
			link_linger(osd, lreq);
		}
	}

	return ct_res;
}