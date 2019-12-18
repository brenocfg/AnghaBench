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
typedef  int /*<<< orphan*/  u32 ;
struct snd_cs46xx {TYPE_1__* card; } ;
struct dsp_pcm_channel_descriptor {TYPE_2__* pcm_reader_scb; } ;
struct TYPE_4__ {int address; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD1024 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD128 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD16 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD256 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD32 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD512 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_MOD64 ; 
 int /*<<< orphan*/  DMA_RQ_C1_SOURCE_SIZE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,int /*<<< orphan*/ ) ; 

int cs46xx_dsp_pcm_channel_set_period (struct snd_cs46xx * chip,
				       struct dsp_pcm_channel_descriptor * pcm_channel,
				       int period_size)
{
	u32 temp = snd_cs46xx_peek (chip,pcm_channel->pcm_reader_scb->address << 2);
	temp &= ~DMA_RQ_C1_SOURCE_SIZE_MASK;

	switch (period_size) {
	case 2048:
		temp |= DMA_RQ_C1_SOURCE_MOD1024;
		break;
	case 1024:
		temp |= DMA_RQ_C1_SOURCE_MOD512;
		break;
	case 512:
		temp |= DMA_RQ_C1_SOURCE_MOD256;
		break;
	case 256:
		temp |= DMA_RQ_C1_SOURCE_MOD128;
		break;
	case 128:
		temp |= DMA_RQ_C1_SOURCE_MOD64;
		break;
	case 64:
		temp |= DMA_RQ_C1_SOURCE_MOD32;
		break;		      
	case 32:
		temp |= DMA_RQ_C1_SOURCE_MOD16;
		break; 
	default:
		dev_dbg(chip->card->dev,
			"period size (%d) not supported by HW\n", period_size);
		return -EINVAL;
	}

	snd_cs46xx_poke (chip,pcm_channel->pcm_reader_scb->address << 2,temp);

	return 0;
}