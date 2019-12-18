#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_DSP_BAR ; 
 int ENODEV ; 
 int SHIM_BYT_CSR_PWAITMODE ; 
 int /*<<< orphan*/  SHIM_BYT_CSR_STALL ; 
 int /*<<< orphan*/  SHIM_CSR ; 
 int SOF_DBG_MBOX ; 
 int SOF_DBG_REGS ; 
 int /*<<< orphan*/  byt_dump (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_sof_dsp_read64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int byt_run(struct snd_sof_dev *sdev)
{
	int tries = 10;

	/* release stall and wait to unstall */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_STALL, 0x0);
	while (tries--) {
		if (!(snd_sof_dsp_read64(sdev, BYT_DSP_BAR, SHIM_CSR) &
		      SHIM_BYT_CSR_PWAITMODE))
			break;
		msleep(100);
	}
	if (tries < 0) {
		dev_err(sdev->dev, "error:  unable to run DSP firmware\n");
		byt_dump(sdev, SOF_DBG_REGS | SOF_DBG_MBOX);
		return -ENODEV;
	}

	/* return init core mask */
	return 1;
}