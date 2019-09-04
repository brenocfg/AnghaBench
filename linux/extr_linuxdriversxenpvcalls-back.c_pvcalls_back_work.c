#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int dummy; } ;
struct xen_pvcalls_request {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  req_cons; } ;
struct pvcalls_fedata {TYPE_1__ ring; int /*<<< orphan*/  irq; struct xenbus_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_COPY_REQUEST (TYPE_1__*,int /*<<< orphan*/ ,struct xen_pvcalls_request*) ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_REQUESTS (TYPE_1__*,int) ; 
 scalar_t__ RING_HAS_UNCONSUMED_REQUESTS (TYPE_1__*) ; 
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (TYPE_1__*,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvcalls_back_handle_cmd (struct xenbus_device*,struct xen_pvcalls_request*) ; 

__attribute__((used)) static void pvcalls_back_work(struct pvcalls_fedata *fedata)
{
	int notify, notify_all = 0, more = 1;
	struct xen_pvcalls_request req;
	struct xenbus_device *dev = fedata->dev;

	while (more) {
		while (RING_HAS_UNCONSUMED_REQUESTS(&fedata->ring)) {
			RING_COPY_REQUEST(&fedata->ring,
					  fedata->ring.req_cons++,
					  &req);

			if (!pvcalls_back_handle_cmd(dev, &req)) {
				RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(
					&fedata->ring, notify);
				notify_all += notify;
			}
		}

		if (notify_all) {
			notify_remote_via_irq(fedata->irq);
			notify_all = 0;
		}

		RING_FINAL_CHECK_FOR_REQUESTS(&fedata->ring, more);
	}
}