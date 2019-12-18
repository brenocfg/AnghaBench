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
 unsigned int DSPDMAC_CHNLSTART_EN_LOBIT ; 
 int /*<<< orphan*/  DSPDMAC_CHNLSTART_INST_OFFSET ; 
 int /*<<< orphan*/  chipio_read (struct hda_codec*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static bool dsp_is_dma_active(struct hda_codec *codec, unsigned int dma_chan)
{
	unsigned int dma_chnlstart_reg;

	chipio_read(codec, DSPDMAC_CHNLSTART_INST_OFFSET, &dma_chnlstart_reg);

	return ((dma_chnlstart_reg & (1 <<
			(DSPDMAC_CHNLSTART_EN_LOBIT + dma_chan))) != 0);
}