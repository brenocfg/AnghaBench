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
 int SHIM_IMRX_BUSY ; 
 int /*<<< orphan*/  SHIM_IPCD ; 
 int SHIM_IPCD_BUSY ; 
 int SHIM_IPCD_DONE ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void bdw_host_done(struct snd_sof_dev *sdev)
{
	/* clear BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IPCD,
					 SHIM_IPCD_BUSY | SHIM_IPCD_DONE,
					 SHIM_IPCD_DONE);

	/* unmask busy interrupt */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IMRX,
					 SHIM_IMRX_BUSY, 0);
}