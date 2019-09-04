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
struct xenbus_device {int dummy; } ;
struct vscsiif_sring {int dummy; } ;
struct TYPE_2__ {scalar_t__ sring; } ;
struct vscsifrnt_info {int irq; TYPE_1__ ring; int /*<<< orphan*/  ring_ref; int /*<<< orphan*/  evtchn; struct xenbus_device* dev; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,struct vscsiif_sring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SHARED_RING_INIT (struct vscsiif_sring*) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int bind_evtchn_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  scsifront_irq_fn ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct vscsifrnt_info*) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_grant_ring (struct xenbus_device*,struct vscsiif_sring*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsifront_alloc_ring(struct vscsifrnt_info *info)
{
	struct xenbus_device *dev = info->dev;
	struct vscsiif_sring *sring;
	grant_ref_t gref;
	int err = -ENOMEM;

	/***** Frontend to Backend ring start *****/
	sring = (struct vscsiif_sring *)__get_free_page(GFP_KERNEL);
	if (!sring) {
		xenbus_dev_fatal(dev, err,
			"fail to allocate shared ring (Front to Back)");
		return err;
	}
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&info->ring, sring, PAGE_SIZE);

	err = xenbus_grant_ring(dev, sring, 1, &gref);
	if (err < 0) {
		free_page((unsigned long)sring);
		xenbus_dev_fatal(dev, err,
			"fail to grant shared ring (Front to Back)");
		return err;
	}
	info->ring_ref = gref;

	err = xenbus_alloc_evtchn(dev, &info->evtchn);
	if (err) {
		xenbus_dev_fatal(dev, err, "xenbus_alloc_evtchn");
		goto free_gnttab;
	}

	err = bind_evtchn_to_irq(info->evtchn);
	if (err <= 0) {
		xenbus_dev_fatal(dev, err, "bind_evtchn_to_irq");
		goto free_gnttab;
	}

	info->irq = err;

	err = request_threaded_irq(info->irq, NULL, scsifront_irq_fn,
				   IRQF_ONESHOT, "scsifront", info);
	if (err) {
		xenbus_dev_fatal(dev, err, "request_threaded_irq");
		goto free_irq;
	}

	return 0;

/* free resource */
free_irq:
	unbind_from_irqhandler(info->irq, info);
free_gnttab:
	gnttab_end_foreign_access(info->ring_ref, 0,
				  (unsigned long)info->ring.sring);

	return err;
}