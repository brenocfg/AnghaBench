#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ i2s_mclk_cfg; scalar_t__ i2s_cfg; } ;
struct cygnus_aio_port {unsigned int bit_per_frame; unsigned int lrclk; unsigned int mclk; int port_type; TYPE_2__* cygaud; TYPE_1__ regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; scalar_t__ audio; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32 ; 
 int I2S_OUT_MCLKRATE_SHIFT ; 
#define  PORT_SPDIF 129 
#define  PORT_TDM 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cygnus_ssp_set_clocks(struct cygnus_aio_port *aio)
{
	u32 value;
	u32 mask = 0xf;
	u32 sclk;
	u32 mclk_rate;
	unsigned int bit_rate;
	unsigned int ratio;

	bit_rate = aio->bit_per_frame * aio->lrclk;

	/*
	 * Check if the bit clock can be generated from the given MCLK.
	 * MCLK must be a perfect multiple of bit clock and must be one of the
	 * following values... (2,4,6,8,10,12,14)
	 */
	if ((aio->mclk % bit_rate) != 0)
		return -EINVAL;

	ratio = aio->mclk / bit_rate;
	switch (ratio) {
	case 2:
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
		mclk_rate = ratio / 2;
		break;

	default:
		dev_err(aio->cygaud->dev,
			"Invalid combination of MCLK and BCLK\n");
		dev_err(aio->cygaud->dev, "lrclk = %u, bits/frame = %u, mclk = %u\n",
			aio->lrclk, aio->bit_per_frame, aio->mclk);
		return -EINVAL;
	}

	/* Set sclk rate */
	switch (aio->port_type) {
	case PORT_TDM:
		sclk = aio->bit_per_frame;
		if (sclk == 512)
			sclk = 0;

		/* sclks_per_1fs_div = sclk cycles/32 */
		sclk /= 32;

		/* Set number of bitclks per frame */
		value = readl(aio->cygaud->audio + aio->regs.i2s_cfg);
		value &= ~(mask << I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32);
		value |= sclk << I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32;
		writel(value, aio->cygaud->audio + aio->regs.i2s_cfg);
		dev_dbg(aio->cygaud->dev,
			"SCLKS_PER_1FS_DIV32 = 0x%x\n", value);
		break;
	case PORT_SPDIF:
		break;
	default:
		dev_err(aio->cygaud->dev, "Unknown port type\n");
		return -EINVAL;
	}

	/* Set MCLK_RATE ssp port (spdif and ssp are the same) */
	value = readl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
	value &= ~(0xf << I2S_OUT_MCLKRATE_SHIFT);
	value |= (mclk_rate << I2S_OUT_MCLKRATE_SHIFT);
	writel(value, aio->cygaud->audio + aio->regs.i2s_mclk_cfg);

	dev_dbg(aio->cygaud->dev, "mclk cfg reg = 0x%x\n", value);
	dev_dbg(aio->cygaud->dev, "bits per frame = %u, mclk = %u Hz, lrclk = %u Hz\n",
			aio->bit_per_frame, aio->mclk, aio->lrclk);
	return 0;
}