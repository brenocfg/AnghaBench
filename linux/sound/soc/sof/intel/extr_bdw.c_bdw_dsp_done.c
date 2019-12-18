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
 int /*<<< orphan*/  SHIM_IMRX ; 
 int /*<<< orphan*/  SHIM_IMRX_DONE ; 
 int /*<<< orphan*/  SHIM_IPCX ; 
 int /*<<< orphan*/  SHIM_IPCX_DONE ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdw_dsp_done(struct snd_sof_dev *sdev)
{
	/* clear DONE bit - tell DSP we have completed */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IPCX,
					 SHIM_IPCX_DONE, 0);

	/* unmask Done interrupt */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IMRX,
					 SHIM_IMRX_DONE, 0);
}