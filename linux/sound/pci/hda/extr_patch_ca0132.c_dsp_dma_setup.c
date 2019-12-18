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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int DSPDMAC_DMACFG_AINCR_LOBIT ; 
 unsigned int DSPDMAC_DMACFG_DBADR_LOBIT ; 
 int /*<<< orphan*/  DSPDMAC_DMACFG_INST_OFFSET (unsigned int) ; 
 int DSPDMAC_DSPADROFS_BOFS_LOBIT ; 
 int /*<<< orphan*/  DSPDMAC_DSPADROFS_INST_OFFSET (unsigned int) ; 
 int DSPDMAC_XFRCNT_BCNT_HIBIT ; 
 unsigned int DSPDMAC_XFRCNT_BCNT_LOBIT ; 
 unsigned int DSPDMAC_XFRCNT_CCNT_LOBIT ; 
 int /*<<< orphan*/  DSPDMAC_XFRCNT_INST_OFFSET (unsigned int) ; 
 int EINVAL ; 
 int ENXIO ; 
 unsigned int INVALID_CHIP_ADDRESS ; 
 int chipio_write (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,...) ; 
 unsigned int dsp_chip_to_dsp_addx (unsigned int,int*,int*) ; 

__attribute__((used)) static int dsp_dma_setup(struct hda_codec *codec,
			unsigned int chip_addx,
			unsigned int count,
			unsigned int dma_chan)
{
	int status = 0;
	bool code, yram;
	unsigned int dsp_addx;
	unsigned int addr_field;
	unsigned int incr_field;
	unsigned int base_cnt;
	unsigned int cur_cnt;
	unsigned int dma_cfg = 0;
	unsigned int adr_ofs = 0;
	unsigned int xfr_cnt = 0;
	const unsigned int max_dma_count = 1 << (DSPDMAC_XFRCNT_BCNT_HIBIT -
						DSPDMAC_XFRCNT_BCNT_LOBIT + 1);

	codec_dbg(codec, "-- dsp_dma_setup() -- Begin ---------\n");

	if (count > max_dma_count) {
		codec_dbg(codec, "count too big\n");
		return -EINVAL;
	}

	dsp_addx = dsp_chip_to_dsp_addx(chip_addx, &code, &yram);
	if (dsp_addx == INVALID_CHIP_ADDRESS) {
		codec_dbg(codec, "invalid chip addr\n");
		return -ENXIO;
	}

	codec_dbg(codec, "   dsp_dma_setup()    start reg pgm\n");

	addr_field = dsp_addx << DSPDMAC_DMACFG_DBADR_LOBIT;
	incr_field   = 0;

	if (!code) {
		addr_field <<= 1;
		if (yram)
			addr_field |= (1 << DSPDMAC_DMACFG_DBADR_LOBIT);

		incr_field  = (1 << DSPDMAC_DMACFG_AINCR_LOBIT);
	}

	dma_cfg = addr_field + incr_field;
	status = chipio_write(codec, DSPDMAC_DMACFG_INST_OFFSET(dma_chan),
				dma_cfg);
	if (status < 0) {
		codec_dbg(codec, "write DMACFG Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup()    Write DMACFG\n");

	adr_ofs = (count - 1) << (DSPDMAC_DSPADROFS_BOFS_LOBIT +
							(code ? 0 : 1));

	status = chipio_write(codec, DSPDMAC_DSPADROFS_INST_OFFSET(dma_chan),
				adr_ofs);
	if (status < 0) {
		codec_dbg(codec, "write DSPADROFS Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup()    Write DSPADROFS\n");

	base_cnt = (count - 1) << DSPDMAC_XFRCNT_BCNT_LOBIT;

	cur_cnt  = (count - 1) << DSPDMAC_XFRCNT_CCNT_LOBIT;

	xfr_cnt = base_cnt | cur_cnt;

	status = chipio_write(codec,
				DSPDMAC_XFRCNT_INST_OFFSET(dma_chan), xfr_cnt);
	if (status < 0) {
		codec_dbg(codec, "write XFRCNT Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup()    Write XFRCNT\n");

	codec_dbg(codec,
		   "ChipA=0x%x, cnt=0x%x, DMACFG=0x%x, "
		   "ADROFS=0x%x, XFRCNT=0x%x\n",
		   chip_addx, count, dma_cfg, adr_ofs, xfr_cnt);

	codec_dbg(codec, "-- dsp_dma_setup() -- Complete ---------\n");

	return 0;
}