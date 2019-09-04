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
 unsigned int DSPDMAC_ACTIVE_AAR_LOBIT ; 
 int DSPDMAC_ACTIVE_AAR_MASK ; 
 int /*<<< orphan*/  DSPDMAC_ACTIVE_INST_OFFSET ; 
 int /*<<< orphan*/  DSPDMAC_AUDCHSEL_INST_OFFSET (unsigned int) ; 
 unsigned int DSPDMAC_CHNLPROP_AC_MASK ; 
 unsigned int DSPDMAC_CHNLPROP_DCON_LOBIT ; 
 int /*<<< orphan*/  DSPDMAC_CHNLPROP_INST_OFFSET ; 
 unsigned int DSPDMAC_CHNLPROP_MSPCE_LOBIT ; 
 unsigned int DSPDMAC_DMA_CFG_CHANNEL_COUNT ; 
 unsigned int DSPDMAC_IRQCNT_BICNT_MASK ; 
 unsigned int DSPDMAC_IRQCNT_CICNT_MASK ; 
 int /*<<< orphan*/  DSPDMAC_IRQCNT_INST_OFFSET (unsigned int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 unsigned int INVALID_CHIP_ADDRESS ; 
 int chipio_read (struct hda_codec*,int /*<<< orphan*/ ,unsigned int*) ; 
 int chipio_write (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,...) ; 
 unsigned int dsp_chip_to_dsp_addx (unsigned int,int*,int*) ; 
 scalar_t__ dsp_is_dma_active (struct hda_codec*,unsigned int) ; 

__attribute__((used)) static int dsp_dma_setup_common(struct hda_codec *codec,
				unsigned int chip_addx,
				unsigned int dma_chan,
				unsigned int port_map_mask,
				bool ovly)
{
	int status = 0;
	unsigned int chnl_prop;
	unsigned int dsp_addx;
	unsigned int active;
	bool code, yram;

	codec_dbg(codec, "-- dsp_dma_setup_common() -- Begin ---------\n");

	if (dma_chan >= DSPDMAC_DMA_CFG_CHANNEL_COUNT) {
		codec_dbg(codec, "dma chan num invalid\n");
		return -EINVAL;
	}

	if (dsp_is_dma_active(codec, dma_chan)) {
		codec_dbg(codec, "dma already active\n");
		return -EBUSY;
	}

	dsp_addx = dsp_chip_to_dsp_addx(chip_addx, &code, &yram);

	if (dsp_addx == INVALID_CHIP_ADDRESS) {
		codec_dbg(codec, "invalid chip addr\n");
		return -ENXIO;
	}

	chnl_prop = DSPDMAC_CHNLPROP_AC_MASK;
	active = 0;

	codec_dbg(codec, "   dsp_dma_setup_common()    start reg pgm\n");

	if (ovly) {
		status = chipio_read(codec, DSPDMAC_CHNLPROP_INST_OFFSET,
				     &chnl_prop);

		if (status < 0) {
			codec_dbg(codec, "read CHNLPROP Reg fail\n");
			return status;
		}
		codec_dbg(codec, "dsp_dma_setup_common() Read CHNLPROP\n");
	}

	if (!code)
		chnl_prop &= ~(1 << (DSPDMAC_CHNLPROP_MSPCE_LOBIT + dma_chan));
	else
		chnl_prop |=  (1 << (DSPDMAC_CHNLPROP_MSPCE_LOBIT + dma_chan));

	chnl_prop &= ~(1 << (DSPDMAC_CHNLPROP_DCON_LOBIT + dma_chan));

	status = chipio_write(codec, DSPDMAC_CHNLPROP_INST_OFFSET, chnl_prop);
	if (status < 0) {
		codec_dbg(codec, "write CHNLPROP Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup_common()    Write CHNLPROP\n");

	if (ovly) {
		status = chipio_read(codec, DSPDMAC_ACTIVE_INST_OFFSET,
				     &active);

		if (status < 0) {
			codec_dbg(codec, "read ACTIVE Reg fail\n");
			return status;
		}
		codec_dbg(codec, "dsp_dma_setup_common() Read ACTIVE\n");
	}

	active &= (~(1 << (DSPDMAC_ACTIVE_AAR_LOBIT + dma_chan))) &
		DSPDMAC_ACTIVE_AAR_MASK;

	status = chipio_write(codec, DSPDMAC_ACTIVE_INST_OFFSET, active);
	if (status < 0) {
		codec_dbg(codec, "write ACTIVE Reg fail\n");
		return status;
	}

	codec_dbg(codec, "   dsp_dma_setup_common()    Write ACTIVE\n");

	status = chipio_write(codec, DSPDMAC_AUDCHSEL_INST_OFFSET(dma_chan),
			      port_map_mask);
	if (status < 0) {
		codec_dbg(codec, "write AUDCHSEL Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup_common()    Write AUDCHSEL\n");

	status = chipio_write(codec, DSPDMAC_IRQCNT_INST_OFFSET(dma_chan),
			DSPDMAC_IRQCNT_BICNT_MASK | DSPDMAC_IRQCNT_CICNT_MASK);
	if (status < 0) {
		codec_dbg(codec, "write IRQCNT Reg fail\n");
		return status;
	}
	codec_dbg(codec, "   dsp_dma_setup_common()    Write IRQCNT\n");

	codec_dbg(codec,
		   "ChipA=0x%x,DspA=0x%x,dmaCh=%u, "
		   "CHSEL=0x%x,CHPROP=0x%x,Active=0x%x\n",
		   chip_addx, dsp_addx, dma_chan,
		   port_map_mask, chnl_prop, active);

	codec_dbg(codec, "-- dsp_dma_setup_common() -- Complete ------\n");

	return 0;
}