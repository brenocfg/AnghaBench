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
typedef  int /*<<< orphan*/  u16 ;
struct snd_cs46xx {int dummy; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_codec_output_scb {int member_10; int member_11; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_SCB_ADDR ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_codec_out_scb(struct snd_cs46xx * chip, char * codec_name,
                                u16 channel_disp, u16 fifo_addr, u16 child_scb_addr,
                                u32 dest, struct dsp_scb_descriptor * parent_scb,
                                int scb_child_type)
{
	struct dsp_scb_descriptor * scb;
  
	struct dsp_codec_output_scb codec_out_scb = {
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
		0,0,
		0,NULL_SCB_ADDR,
		0,                      /* COstrmRsConfig */
		0,                      /* COstrmBufPtr */
		channel_disp,fifo_addr, /* leftChanBaseIOaddr:rightChanIOdisp */
		0x0000,0x0080,          /* (!AC97!) COexpVolChangeRate:COscaleShiftCount */
		0,child_scb_addr        /* COreserved - need child scb to work with rom code */
	};
  
  
	scb = cs46xx_dsp_create_generic_scb(chip,codec_name,(u32 *)&codec_out_scb,
					    dest,"S16_CODECOUTPUTTASK",parent_scb,
					    scb_child_type);
  
	return scb;
}