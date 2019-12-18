#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int chnl_alloc; } ;
union aud_info_frame3 {int regval; TYPE_2__ regx; } ;
struct TYPE_7__ {int chnl_cnt; int chksum; } ;
union aud_info_frame2 {int regval; TYPE_3__ regx; } ;
struct TYPE_8__ {int dip_freq; int dip_en_sta; } ;
union aud_ctrl_st {int regval; TYPE_4__ regx; } ;
typedef  int u8 ;
typedef  int u32 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_intelhad {scalar_t__ dp_output; } ;
struct TYPE_5__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CNTL_ST ; 
 int /*<<< orphan*/  AUD_HDMIW_INFOFR ; 
 int BYTES_PER_WORD ; 
 int DP_INFO_FRAME_WORD1 ; 
 int HAD_MAX_DIP_WORDS ; 
 int HDMI_INFO_FRAME_WORD1 ; 
 int VALID_DIP_WORDS ; 
 int had_channel_allocation (struct snd_intelhad*,int) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void had_prog_dip(struct snd_pcm_substream *substream,
			 struct snd_intelhad *intelhaddata)
{
	int i;
	union aud_ctrl_st ctrl_state = {.regval = 0};
	union aud_info_frame2 frame2 = {.regval = 0};
	union aud_info_frame3 frame3 = {.regval = 0};
	u8 checksum = 0;
	u32 info_frame;
	int channels;
	int ca;

	channels = substream->runtime->channels;

	had_write_register(intelhaddata, AUD_CNTL_ST, ctrl_state.regval);

	ca = had_channel_allocation(intelhaddata, channels);
	if (intelhaddata->dp_output) {
		info_frame = DP_INFO_FRAME_WORD1;
		frame2.regval = (substream->runtime->channels - 1) | (ca << 24);
	} else {
		info_frame = HDMI_INFO_FRAME_WORD1;
		frame2.regx.chnl_cnt = substream->runtime->channels - 1;
		frame3.regx.chnl_alloc = ca;

		/* Calculte the byte wide checksum for all valid DIP words */
		for (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (info_frame >> (i * 8)) & 0xff;
		for (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (frame2.regval >> (i * 8)) & 0xff;
		for (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (frame3.regval >> (i * 8)) & 0xff;

		frame2.regx.chksum = -(checksum);
	}

	had_write_register(intelhaddata, AUD_HDMIW_INFOFR, info_frame);
	had_write_register(intelhaddata, AUD_HDMIW_INFOFR, frame2.regval);
	had_write_register(intelhaddata, AUD_HDMIW_INFOFR, frame3.regval);

	/* program remaining DIP words with zero */
	for (i = 0; i < HAD_MAX_DIP_WORDS-VALID_DIP_WORDS; i++)
		had_write_register(intelhaddata, AUD_HDMIW_INFOFR, 0x0);

	ctrl_state.regx.dip_freq = 1;
	ctrl_state.regx.dip_en_sta = 1;
	had_write_register(intelhaddata, AUD_CNTL_ST, ctrl_state.regval);
}