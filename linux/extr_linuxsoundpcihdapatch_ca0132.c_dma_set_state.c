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
struct dma_engine {int /*<<< orphan*/  codec; } ;
typedef  enum dma_state { ____Placeholder_dma_state } dma_state ;

/* Variables and functions */
#define  DMA_STATE_RUN 129 
#define  DMA_STATE_STOP 128 
 int /*<<< orphan*/  snd_hda_codec_load_dsp_trigger (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dma_set_state(struct dma_engine *dma, enum dma_state state)
{
	bool cmd;

	switch (state) {
	case DMA_STATE_STOP:
		cmd = false;
		break;
	case DMA_STATE_RUN:
		cmd = true;
		break;
	default:
		return 0;
	}

	snd_hda_codec_load_dsp_trigger(dma->codec, cmd);
	return 0;
}