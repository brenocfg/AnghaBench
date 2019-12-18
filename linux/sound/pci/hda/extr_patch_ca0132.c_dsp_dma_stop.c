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
 unsigned int DSPDMAC_CHNLSTART_DIS_LOBIT ; 
 unsigned int DSPDMAC_CHNLSTART_DIS_MASK ; 
 unsigned int DSPDMAC_CHNLSTART_EN_MASK ; 
 int /*<<< orphan*/  DSPDMAC_CHNLSTART_INST_OFFSET ; 
 int chipio_read (struct hda_codec*,int /*<<< orphan*/ ,unsigned int*) ; 
 int chipio_write (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 

__attribute__((used)) static int dsp_dma_stop(struct hda_codec *codec,
			unsigned int dma_chan, bool ovly)
{
	unsigned int reg = 0;
	int status = 0;

	codec_dbg(codec, "-- dsp_dma_stop() -- Begin ---------\n");

	if (ovly) {
		status = chipio_read(codec,
				     DSPDMAC_CHNLSTART_INST_OFFSET, &reg);

		if (status < 0) {
			codec_dbg(codec, "read CHNLSTART reg fail\n");
			return status;
		}
		codec_dbg(codec, "-- dsp_dma_stop()    Read CHNLSTART\n");
		reg &= ~(DSPDMAC_CHNLSTART_EN_MASK |
				DSPDMAC_CHNLSTART_DIS_MASK);
	}

	status = chipio_write(codec, DSPDMAC_CHNLSTART_INST_OFFSET,
			reg | (1 << (dma_chan + DSPDMAC_CHNLSTART_DIS_LOBIT)));
	if (status < 0) {
		codec_dbg(codec, "write CHNLSTART reg fail\n");
		return status;
	}
	codec_dbg(codec, "-- dsp_dma_stop() -- Complete ---------\n");

	return status;
}