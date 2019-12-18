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
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_SD_BDLPLBA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_SD_CTL_DEIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_SD_CTL_DEIE_MASK ; 
 int /*<<< orphan*/  CL_SD_CTL_FEIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_SD_CTL_FEIE_MASK ; 
 int /*<<< orphan*/  CL_SD_CTL_IOCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_SD_CTL_IOCE_MASK ; 
 int /*<<< orphan*/  CL_SD_CTL_STRM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_SD_CTL_STRM_MASK ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_BDLPL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_BDLPU ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_CBL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_CTL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_LVI ; 
 int /*<<< orphan*/  skl_cldma_stream_run (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_write (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_cldma_stream_clear(struct sst_dsp  *ctx)
{
	/* make sure Run bit is cleared before setting stream register */
	skl_cldma_stream_run(ctx, 0);

	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_IOCE_MASK, CL_SD_CTL_IOCE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_FEIE_MASK, CL_SD_CTL_FEIE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_DEIE_MASK, CL_SD_CTL_DEIE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_STRM_MASK, CL_SD_CTL_STRM(0));

	sst_dsp_shim_write(ctx, SKL_ADSP_REG_CL_SD_BDLPL, CL_SD_BDLPLBA(0));
	sst_dsp_shim_write(ctx, SKL_ADSP_REG_CL_SD_BDLPU, 0);

	sst_dsp_shim_write(ctx, SKL_ADSP_REG_CL_SD_CBL, 0);
	sst_dsp_shim_write(ctx, SKL_ADSP_REG_CL_SD_LVI, 0);
}