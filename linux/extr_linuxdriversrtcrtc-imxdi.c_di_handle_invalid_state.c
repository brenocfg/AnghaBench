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
 int DCR_TCE ; 
 int DCR_TCHL ; 
 int DCR_TCSL ; 
 int DCR_TDCSL ; 
 scalar_t__ DSR ; 
 int DSR_NVF ; 
 int DSR_TCO ; 
 scalar_t__ DTCMR ; 
 scalar_t__ DTCR ; 
 int ENODEV ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int di_handle_valid_state (struct imxdi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_what_is_to_be_done (struct imxdi_dev*,char*) ; 
 int /*<<< orphan*/  di_write_busy_wait (struct imxdi_dev*,int,scalar_t__) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int di_handle_invalid_state(struct imxdi_dev *imxdi, u32 dsr)
{
	u32 dcr, sec;

	/*
	 * lets disable all sources which can force the DryIce unit into
	 * the "FAILURE STATE" for now
	 */
	di_write_busy_wait(imxdi, 0x00000000, DTCR);
	/* and lets protect them at runtime from any change */
	di_write_busy_wait(imxdi, DCR_TDCSL, DCR);

	sec = readl(imxdi->ioaddr + DTCMR);
	if (sec != 0)
		dev_warn(&imxdi->pdev->dev,
			 "The security violation has happened at %u seconds\n",
			 sec);
	/*
	 * the timer cannot be set/modified if
	 * - the TCHL or TCSL bit is set in DCR
	 */
	dcr = readl(imxdi->ioaddr + DCR);
	if (!(dcr & DCR_TCE)) {
		if (dcr & DCR_TCHL) {
			/* we are out of luck */
			di_what_is_to_be_done(imxdi, "battery");
			return -ENODEV;
		}
		if (dcr & DCR_TCSL) {
			di_what_is_to_be_done(imxdi, "main");
			return -ENODEV;
		}
	}
	/*
	 * - the timer counter stops/is stopped if
	 *   - its overflow flag is set (TCO in DSR)
	 *      -> clear overflow bit to make it count again
	 *   - NVF is set in DSR
	 *      -> clear non-valid bit to make it count again
	 *   - its TCE (DCR) is cleared
	 *      -> set TCE to make it count
	 *   - it was never set before
	 *      -> write a time into it (required again if the NVF was set)
	 */
	/* state handled */
	di_write_busy_wait(imxdi, DSR_NVF, DSR);
	/* clear overflow flag */
	di_write_busy_wait(imxdi, DSR_TCO, DSR);
	/* enable the counter */
	di_write_busy_wait(imxdi, dcr | DCR_TCE, DCR);
	/* set and trigger it to make it count */
	di_write_busy_wait(imxdi, sec, DTCMR);

	/* now prepare for the valid state */
	return di_handle_valid_state(imxdi, __raw_readl(imxdi->ioaddr + DSR));
}