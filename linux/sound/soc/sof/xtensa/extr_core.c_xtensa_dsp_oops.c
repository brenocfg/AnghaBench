#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_dsp_oops_xtensa {scalar_t__ exccause; scalar_t__ epc1; scalar_t__ epc5; scalar_t__ eps2; scalar_t__ eps6; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  intenable; int /*<<< orphan*/  eps7; int /*<<< orphan*/  eps5; int /*<<< orphan*/  eps4; int /*<<< orphan*/  eps3; int /*<<< orphan*/  depc; int /*<<< orphan*/  epc7; int /*<<< orphan*/  epc6; int /*<<< orphan*/  epc4; int /*<<< orphan*/  epc3; int /*<<< orphan*/  epc2; int /*<<< orphan*/  sar; int /*<<< orphan*/  ps; int /*<<< orphan*/  excvaddr; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  description; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* xtensa_exception_causes ; 

__attribute__((used)) static void xtensa_dsp_oops(struct snd_sof_dev *sdev, void *oops)
{
	struct sof_ipc_dsp_oops_xtensa *xoops = oops;
	int i;

	dev_err(sdev->dev, "error: DSP Firmware Oops\n");
	for (i = 0; i < ARRAY_SIZE(xtensa_exception_causes); i++) {
		if (xtensa_exception_causes[i].id == xoops->exccause) {
			dev_err(sdev->dev, "error: Exception Cause: %s, %s\n",
				xtensa_exception_causes[i].msg,
				xtensa_exception_causes[i].description);
		}
	}
	dev_err(sdev->dev, "EXCCAUSE 0x%8.8x EXCVADDR 0x%8.8x PS       0x%8.8x SAR     0x%8.8x\n",
		xoops->exccause, xoops->excvaddr, xoops->ps, xoops->sar);
	dev_err(sdev->dev, "EPC1     0x%8.8x EPC2     0x%8.8x EPC3     0x%8.8x EPC4    0x%8.8x",
		xoops->epc1, xoops->epc2, xoops->epc3, xoops->epc4);
	dev_err(sdev->dev, "EPC5     0x%8.8x EPC6     0x%8.8x EPC7     0x%8.8x DEPC    0x%8.8x",
		xoops->epc5, xoops->epc6, xoops->epc7, xoops->depc);
	dev_err(sdev->dev, "EPS2     0x%8.8x EPS3     0x%8.8x EPS4     0x%8.8x EPS5    0x%8.8x",
		xoops->eps2, xoops->eps3, xoops->eps4, xoops->eps5);
	dev_err(sdev->dev, "EPS6     0x%8.8x EPS7     0x%8.8x INTENABL 0x%8.8x INTERRU 0x%8.8x",
		xoops->eps6, xoops->eps7, xoops->intenable, xoops->interrupt);
}