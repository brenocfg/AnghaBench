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
struct platform_device {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct mpsc_shared_pdata {int /*<<< orphan*/  intr_mask_val; int /*<<< orphan*/  intr_cause_val; int /*<<< orphan*/  tcrr_val; int /*<<< orphan*/  rcrr_val; int /*<<< orphan*/  mrr_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  SDMA_INTR_MASK_m; int /*<<< orphan*/  SDMA_INTR_CAUSE_m; int /*<<< orphan*/  MPSC_TCRR_m; int /*<<< orphan*/  MPSC_RCRR_m; int /*<<< orphan*/  MPSC_MRR_m; } ;

/* Variables and functions */
 int ENODEV ; 
 struct mpsc_shared_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int mpsc_shared_map_regs (struct platform_device*) ; 
 TYPE_1__ mpsc_shared_regs ; 

__attribute__((used)) static int mpsc_shared_drv_probe(struct platform_device *dev)
{
	struct mpsc_shared_pdata	*pdata;
	int rc;

	if (dev->id != 0)
		return -ENODEV;

	rc = mpsc_shared_map_regs(dev);
	if (rc)
		return rc;

	pdata = dev_get_platdata(&dev->dev);

	mpsc_shared_regs.MPSC_MRR_m = pdata->mrr_val;
	mpsc_shared_regs.MPSC_RCRR_m= pdata->rcrr_val;
	mpsc_shared_regs.MPSC_TCRR_m= pdata->tcrr_val;
	mpsc_shared_regs.SDMA_INTR_CAUSE_m = pdata->intr_cause_val;
	mpsc_shared_regs.SDMA_INTR_MASK_m = pdata->intr_mask_val;

	return 0;
}