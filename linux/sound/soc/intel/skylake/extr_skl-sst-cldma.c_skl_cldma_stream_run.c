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
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_SD_CTL_RUN (int) ; 
 unsigned char CL_SD_CTL_RUN_MASK ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_CTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned char,int) ; 
 unsigned char sst_dsp_shim_read (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void skl_cldma_stream_run(struct sst_dsp  *ctx, bool enable)
{
	unsigned char val;
	int timeout;

	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_RUN_MASK, CL_SD_CTL_RUN(enable));

	udelay(3);
	timeout = 300;
	do {
		/* waiting for hardware to report that the stream Run bit set */
		val = sst_dsp_shim_read(ctx, SKL_ADSP_REG_CL_SD_CTL) &
			CL_SD_CTL_RUN_MASK;
		if (enable && val)
			break;
		else if (!enable && !val)
			break;
		udelay(3);
	} while (--timeout);

	if (timeout == 0)
		dev_err(ctx->dev, "Failed to set Run bit=%d enable=%d\n", val, enable);
}