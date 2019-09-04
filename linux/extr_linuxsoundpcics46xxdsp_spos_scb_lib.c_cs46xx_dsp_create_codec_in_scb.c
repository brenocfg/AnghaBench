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
typedef  int u16 ;
struct snd_cs46xx {int dummy; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_codec_input_scb {int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; scalar_t__ member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;

/* Variables and functions */
 scalar_t__ RSCONFIG_MODULO_64 ; 
 scalar_t__ RSCONFIG_SAMPLE_16STEREO ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_codec_in_scb(struct snd_cs46xx * chip, char * codec_name,
			       u16 channel_disp, u16 fifo_addr, u16 sample_buffer_addr,
			       u32 dest, struct dsp_scb_descriptor * parent_scb,
			       int scb_child_type)
{

	struct dsp_scb_descriptor * scb;
	struct dsp_codec_input_scb codec_input_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{
			0,
			0,
			0,
			0,
			0
		},
    
#if 0  /* cs4620 */
		SyncIOSCB,NULL_SCB_ADDR
#else
		0 , 0,
#endif
		0,0,

		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,  /* strmRsConfig */
		sample_buffer_addr << 0x10,       /* strmBufPtr; defined as a dword ptr, used as a byte ptr */
		channel_disp,fifo_addr,           /* (!AC97!) leftChanBaseINaddr=AC97primary 
						     link input slot 3 :rightChanINdisp=""slot 4 */
		0x0000,0x0000,                    /* (!AC97!) ????:scaleShiftCount; no shift needed 
						     because AC97 is already 20 bits */
		0x80008000                        /* ??clw cwcgame.scb has 0 */
	};
  
	scb = cs46xx_dsp_create_generic_scb(chip,codec_name,(u32 *)&codec_input_scb,
					    dest,"S16_CODECINPUTTASK",parent_scb,
					    scb_child_type);
	return scb;
}