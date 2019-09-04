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
struct TYPE_5__ {int /*<<< orphan*/  scsw; } ;
struct subchannel {TYPE_2__ schib; } ;
struct cmb_data {int /*<<< orphan*/  last_update; int /*<<< orphan*/  size; int /*<<< orphan*/  last_block; void* hw_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
struct TYPE_6__ {struct cmb_data* cmb; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int SCSW_ACTL_DEVACT ; 
 int SCSW_ACTL_SCHACT ; 
 int SCSW_ACTL_SUSPENDED ; 
 int SCSW_FCTL_START_FUNC ; 
 int SCSW_STCTL_SEC_STATUS ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int scsw_actl (int /*<<< orphan*/ *) ; 
 int scsw_fctl (int /*<<< orphan*/ *) ; 
 int scsw_stctl (int /*<<< orphan*/ *) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmf_copy_block(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct cmb_data *cmb_data;
	void *hw_block;

	if (cio_update_schib(sch))
		return -ENODEV;

	if (scsw_fctl(&sch->schib.scsw) & SCSW_FCTL_START_FUNC) {
		/* Don't copy if a start function is in progress. */
		if ((!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_SUSPENDED)) &&
		    (scsw_actl(&sch->schib.scsw) &
		     (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT)) &&
		    (!(scsw_stctl(&sch->schib.scsw) & SCSW_STCTL_SEC_STATUS)))
			return -EBUSY;
	}
	cmb_data = cdev->private->cmb;
	hw_block = cmb_data->hw_block;
	memcpy(cmb_data->last_block, hw_block, cmb_data->size);
	cmb_data->last_update = get_tod_clock();
	return 0;
}