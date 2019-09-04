#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
struct TYPE_5__ {TYPE_1__ base_oloc; } ;
struct ceph_osd_request {int r_flags; TYPE_2__ r_t; struct ceph_osd_client* r_osdc; } ;
struct ceph_osd_client {TYPE_3__* osdmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  epoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSDMAP_FULL ; 
 int CEPH_OSD_FLAG_WRITE ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  abort_request (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_osdmap_flag (struct ceph_osd_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ pool_full (struct ceph_osd_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_epoch_barrier (struct ceph_osd_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abort_on_full_fn(struct ceph_osd_request *req, void *arg)
{
	struct ceph_osd_client *osdc = req->r_osdc;
	bool *victims = arg;

	if ((req->r_flags & CEPH_OSD_FLAG_WRITE) &&
	    (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) ||
	     pool_full(osdc, req->r_t.base_oloc.pool))) {
		if (!*victims) {
			update_epoch_barrier(osdc, osdc->osdmap->epoch);
			*victims = true;
		}
		abort_request(req, -ENOSPC);
	}

	return 0; /* continue iteration */
}