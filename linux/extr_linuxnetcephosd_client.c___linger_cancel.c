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
struct ceph_osd_linger_request {int /*<<< orphan*/  osd; TYPE_1__* reg_req; TYPE_1__* ping_req; scalar_t__ is_watch; } ;
struct TYPE_2__ {scalar_t__ r_osd; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_linger_map_check (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  cancel_linger_request (TYPE_1__*) ; 
 int /*<<< orphan*/  linger_unregister (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  unlink_linger (int /*<<< orphan*/ ,struct ceph_osd_linger_request*) ; 

__attribute__((used)) static void __linger_cancel(struct ceph_osd_linger_request *lreq)
{
	if (lreq->is_watch && lreq->ping_req->r_osd)
		cancel_linger_request(lreq->ping_req);
	if (lreq->reg_req->r_osd)
		cancel_linger_request(lreq->reg_req);
	cancel_linger_map_check(lreq);
	unlink_linger(lreq->osd, lreq);
	linger_unregister(lreq);
}