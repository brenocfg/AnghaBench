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
typedef  int u32 ;
struct imxdi_dev {scalar_t__ ioaddr; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DCR ; 
 int DCR_FSHL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  di_report_tamper_info (struct imxdi_dev*,int) ; 
 int /*<<< orphan*/  di_what_is_to_be_done (struct imxdi_dev*,char*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int di_handle_failure_state(struct imxdi_dev *imxdi, u32 dsr)
{
	u32 dcr;

	dev_dbg(&imxdi->pdev->dev, "DSR register reports: %08X\n", dsr);

	/* report the cause */
	di_report_tamper_info(imxdi, dsr);

	dcr = readl(imxdi->ioaddr + DCR);

	if (dcr & DCR_FSHL) {
		/* we are out of luck */
		di_what_is_to_be_done(imxdi, "battery");
		return -ENODEV;
	}
	/*
	 * with the next SYSTEM POR we will transit from the "FAILURE STATE"
	 * into the "NON-VALID STATE" + "FAILURE STATE"
	 */
	di_what_is_to_be_done(imxdi, "main");

	return -ENODEV;
}