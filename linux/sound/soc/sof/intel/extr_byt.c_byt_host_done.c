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
 int /*<<< orphan*/  BYT_DSP_BAR ; 
 int SHIM_BYT_IPCD_BUSY ; 
 int SHIM_BYT_IPCD_DONE ; 
 int /*<<< orphan*/  SHIM_IMRX ; 
 int SHIM_IMRX_BUSY ; 
 int /*<<< orphan*/  SHIM_IPCD ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits64_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void byt_host_done(struct snd_sof_dev *sdev)
{
	/* clear BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IPCD,
					   SHIM_BYT_IPCD_BUSY |
					   SHIM_BYT_IPCD_DONE,
					   SHIM_BYT_IPCD_DONE);

	/* unmask busy interrupt */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IMRX,
					   SHIM_IMRX_BUSY, 0);
}