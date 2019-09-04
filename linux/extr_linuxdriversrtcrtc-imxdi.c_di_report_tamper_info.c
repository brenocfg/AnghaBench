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
struct imxdi_dev {TYPE_1__* pdev; scalar_t__ ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSR_CTD ; 
 int DSR_EBD ; 
 int DSR_ETAD ; 
 int DSR_ETBD ; 
 int DSR_MCO ; 
 int DSR_SAD ; 
 int DSR_TCO ; 
 int DSR_TTD ; 
 int DSR_VTD ; 
 int DSR_WTD ; 
 scalar_t__ DTCR ; 
 int DTCR_CTE ; 
 int DTCR_EBE ; 
 int DTCR_ETAE ; 
 int DTCR_ETBE ; 
 int DTCR_MOE ; 
 int DTCR_SAIE ; 
 int DTCR_TOE ; 
 int DTCR_TTE ; 
 int DTCR_VTE ; 
 int DTCR_WTE ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ *,char*,...) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void di_report_tamper_info(struct imxdi_dev *imxdi,  u32 dsr)
{
	u32 dtcr;

	dtcr = readl(imxdi->ioaddr + DTCR);

	dev_emerg(&imxdi->pdev->dev, "DryIce tamper event detected\n");
	/* the following flags force a transition into the "FAILURE STATE" */
	if (dsr & DSR_VTD)
		dev_emerg(&imxdi->pdev->dev, "%sVoltage Tamper Event\n",
			  dtcr & DTCR_VTE ? "" : "Spurious ");

	if (dsr & DSR_CTD)
		dev_emerg(&imxdi->pdev->dev, "%s32768 Hz Clock Tamper Event\n",
			  dtcr & DTCR_CTE ? "" : "Spurious ");

	if (dsr & DSR_TTD)
		dev_emerg(&imxdi->pdev->dev, "%sTemperature Tamper Event\n",
			  dtcr & DTCR_TTE ? "" : "Spurious ");

	if (dsr & DSR_SAD)
		dev_emerg(&imxdi->pdev->dev,
			  "%sSecure Controller Alarm Event\n",
			  dtcr & DTCR_SAIE ? "" : "Spurious ");

	if (dsr & DSR_EBD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Boot Tamper Event\n",
			  dtcr & DTCR_EBE ? "" : "Spurious ");

	if (dsr & DSR_ETAD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Tamper A Event\n",
			  dtcr & DTCR_ETAE ? "" : "Spurious ");

	if (dsr & DSR_ETBD)
		dev_emerg(&imxdi->pdev->dev, "%sExternal Tamper B Event\n",
			  dtcr & DTCR_ETBE ? "" : "Spurious ");

	if (dsr & DSR_WTD)
		dev_emerg(&imxdi->pdev->dev, "%sWire-mesh Tamper Event\n",
			  dtcr & DTCR_WTE ? "" : "Spurious ");

	if (dsr & DSR_MCO)
		dev_emerg(&imxdi->pdev->dev,
			  "%sMonotonic-counter Overflow Event\n",
			  dtcr & DTCR_MOE ? "" : "Spurious ");

	if (dsr & DSR_TCO)
		dev_emerg(&imxdi->pdev->dev, "%sTimer-counter Overflow Event\n",
			  dtcr & DTCR_TOE ? "" : "Spurious ");
}