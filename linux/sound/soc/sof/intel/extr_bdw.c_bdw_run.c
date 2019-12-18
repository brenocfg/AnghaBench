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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDW_DSP_BAR ; 
 int /*<<< orphan*/  SHIM_CSR ; 
 int /*<<< orphan*/  SHIM_CSR_STALL ; 
 int /*<<< orphan*/  SHIM_HMDC ; 
 int SHIM_HMDC_HDDA_E0_ALLCH ; 
 int SHIM_HMDC_HDDA_E1_ALLCH ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bdw_run(struct snd_sof_dev *sdev)
{
	/* set opportunistic mode on engine 0,1 for all channels */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH, 0);

	/* set DSP to RUN */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_STALL, 0x0);

	/* return init core mask */
	return 1;
}