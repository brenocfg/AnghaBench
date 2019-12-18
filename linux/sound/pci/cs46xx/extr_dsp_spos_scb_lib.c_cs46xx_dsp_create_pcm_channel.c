#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_cs46xx {int /*<<< orphan*/  reg_lock; TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int nsrc_scb; int* src_scb_slots; scalar_t__ the_null_scb; struct dsp_pcm_channel_descriptor* pcm_channels; int /*<<< orphan*/  npcm_channels; struct dsp_scb_descriptor* asynch_tx_scb; struct dsp_scb_descriptor* center_lfe_mix_scb; struct dsp_scb_descriptor* rear_mix_scb; struct dsp_scb_descriptor* master_mix_scb; } ;
struct dsp_scb_descriptor {scalar_t__ sub_list_ptr; int /*<<< orphan*/  ref_count; } ;
struct dsp_pcm_channel_descriptor {int active; int sample_rate; int src_slot; int unlinked; int pcm_slot; struct dsp_scb_descriptor* mixer_scb; void* private_data; struct dsp_scb_descriptor* src_scb; struct dsp_scb_descriptor* pcm_reader_scb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CS46XX_DSP_CAPTURE_CHANNEL ; 
#define  DSP_IEC958_CHANNEL 132 
 int DSP_MAX_PCM_CHANNELS ; 
 int DSP_MAX_SCB_NAME ; 
 int DSP_MAX_SRC_NR ; 
#define  DSP_PCM_CENTER_LFE_CHANNEL 131 
#define  DSP_PCM_MAIN_CHANNEL 130 
#define  DSP_PCM_REAR_CHANNEL 129 
#define  DSP_PCM_S71_CHANNEL 128 
 int SCB_ON_PARENT_NEXT_SCB ; 
 int SCB_ON_PARENT_SUBLIST_SCB ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_pcm_reader_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_src_task_scb (struct snd_cs46xx*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dsp_scb_descriptor*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct dsp_scb_descriptor* find_next_free_scb (struct snd_cs46xx*,scalar_t__) ; 
 int /*<<< orphan*/ * pcm_reader_buffer_addr ; 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * src_delay_buffer_addr ; 
 int /*<<< orphan*/ * src_output_buffer_addr ; 

struct dsp_pcm_channel_descriptor *
cs46xx_dsp_create_pcm_channel (struct snd_cs46xx * chip,
			       u32 sample_rate, void * private_data, 
			       u32 hw_dma_addr,
			       int pcm_channel_id)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * src_scb = NULL, * pcm_scb, * mixer_scb = NULL;
	struct dsp_scb_descriptor * src_parent_scb = NULL;

	/* struct dsp_scb_descriptor * pcm_parent_scb; */
	char scb_name[DSP_MAX_SCB_NAME];
	int i, pcm_index = -1, insert_point, src_index = -1, pass_through = 0;
	unsigned long flags;

	switch (pcm_channel_id) {
	case DSP_PCM_MAIN_CHANNEL:
		mixer_scb = ins->master_mix_scb;
		break;
	case DSP_PCM_REAR_CHANNEL:
		mixer_scb = ins->rear_mix_scb;
		break;
	case DSP_PCM_CENTER_LFE_CHANNEL:
		mixer_scb = ins->center_lfe_mix_scb;
		break;
	case DSP_PCM_S71_CHANNEL:
		/* TODO */
		snd_BUG();
		break;
	case DSP_IEC958_CHANNEL:
		if (snd_BUG_ON(!ins->asynch_tx_scb))
			return NULL;
		mixer_scb = ins->asynch_tx_scb;

		/* if sample rate is set to 48khz we pass
		   the Sample Rate Converted (which could
		   alter the raw data stream ...) */
		if (sample_rate == 48000) {
			dev_dbg(chip->card->dev, "IEC958 pass through\n");
			/* Hack to bypass creating a new SRC */
			pass_through = 1;
		}
		break;
	default:
		snd_BUG();
		return NULL;
	}
	/* default sample rate is 44100 */
	if (!sample_rate) sample_rate = 44100;

	/* search for a already created SRC SCB with the same sample rate */
	for (i = 0; i < DSP_MAX_PCM_CHANNELS && 
		     (pcm_index == -1 || src_scb == NULL); ++i) {

		/* virtual channel reserved 
		   for capture */
		if (i == CS46XX_DSP_CAPTURE_CHANNEL) continue;

		if (ins->pcm_channels[i].active) {
			if (!src_scb && 
			    ins->pcm_channels[i].sample_rate == sample_rate &&
			    ins->pcm_channels[i].mixer_scb == mixer_scb) {
				src_scb = ins->pcm_channels[i].src_scb;
				ins->pcm_channels[i].src_scb->ref_count ++;
				src_index = ins->pcm_channels[i].src_slot;
			}
		} else if (pcm_index == -1) {
			pcm_index = i;
		}
	}

	if (pcm_index == -1) {
		dev_err(chip->card->dev, "dsp_spos: no free PCM channel\n");
		return NULL;
	}

	if (src_scb == NULL) {
		if (ins->nsrc_scb >= DSP_MAX_SRC_NR) {
			dev_err(chip->card->dev,
				"dsp_spos: to many SRC instances\n!");
			return NULL;
		}

		/* find a free slot */
		for (i = 0; i < DSP_MAX_SRC_NR; ++i) {
			if (ins->src_scb_slots[i] == 0) {
				src_index = i;
				ins->src_scb_slots[i] = 1;
				break;
			}
		}
		if (snd_BUG_ON(src_index == -1))
			return NULL;

		/* we need to create a new SRC SCB */
		if (mixer_scb->sub_list_ptr == ins->the_null_scb) {
			src_parent_scb = mixer_scb;
			insert_point = SCB_ON_PARENT_SUBLIST_SCB;
		} else {
			src_parent_scb = find_next_free_scb(chip,mixer_scb->sub_list_ptr);
			insert_point = SCB_ON_PARENT_NEXT_SCB;
		}

		snprintf (scb_name,DSP_MAX_SCB_NAME,"SrcTask_SCB%d",src_index);
		
		dev_dbg(chip->card->dev,
			"dsp_spos: creating SRC \"%s\"\n", scb_name);
		src_scb = cs46xx_dsp_create_src_task_scb(chip,scb_name,
							 sample_rate,
							 src_output_buffer_addr[src_index],
							 src_delay_buffer_addr[src_index],
							 /* 0x400 - 0x600 source SCBs */
							 0x400 + (src_index * 0x10) ,
							 src_parent_scb,
							 insert_point,
							 pass_through);

		if (!src_scb) {
			dev_err(chip->card->dev,
				"dsp_spos: failed to create SRCtaskSCB\n");
			return NULL;
		}

		/* cs46xx_dsp_set_src_sample_rate(chip,src_scb,sample_rate); */

		ins->nsrc_scb ++;
	} 
  
  
	snprintf (scb_name,DSP_MAX_SCB_NAME,"PCMReader_SCB%d",pcm_index);

	dev_dbg(chip->card->dev, "dsp_spos: creating PCM \"%s\" (%d)\n",
		scb_name, pcm_channel_id);

	pcm_scb = cs46xx_dsp_create_pcm_reader_scb(chip,scb_name,
						   pcm_reader_buffer_addr[pcm_index],
						   /* 0x200 - 400 PCMreader SCBs */
						   (pcm_index * 0x10) + 0x200,
						   pcm_index,    /* virtual channel 0-31 */
						   hw_dma_addr,  /* pcm hw addr */
                           NULL,         /* parent SCB ptr */
                           0             /* insert point */ 
                           );

	if (!pcm_scb) {
		dev_err(chip->card->dev,
			"dsp_spos: failed to create PCMreaderSCB\n");
		return NULL;
	}
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ins->pcm_channels[pcm_index].sample_rate = sample_rate;
	ins->pcm_channels[pcm_index].pcm_reader_scb = pcm_scb;
	ins->pcm_channels[pcm_index].src_scb = src_scb;
	ins->pcm_channels[pcm_index].unlinked = 1;
	ins->pcm_channels[pcm_index].private_data = private_data;
	ins->pcm_channels[pcm_index].src_slot = src_index;
	ins->pcm_channels[pcm_index].active = 1;
	ins->pcm_channels[pcm_index].pcm_slot = pcm_index;
	ins->pcm_channels[pcm_index].mixer_scb = mixer_scb;
	ins->npcm_channels ++;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	return (ins->pcm_channels + pcm_index);
}