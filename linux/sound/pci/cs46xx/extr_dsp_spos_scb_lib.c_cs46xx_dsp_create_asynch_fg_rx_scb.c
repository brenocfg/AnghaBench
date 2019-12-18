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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int /*<<< orphan*/  spdif_input_volume_left; int /*<<< orphan*/  spdif_input_volume_right; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_asynch_fg_rx_scb {int member_0; int member_1; int member_2; int member_3; int member_13; int member_14; int member_15; int /*<<< orphan*/  member_19; int /*<<< orphan*/  member_18; int /*<<< orphan*/  member_17; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; TYPE_1__ member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; } ;

/* Variables and functions */
 int RSCONFIG_MODULO_128 ; 
 int RSCONFIG_SAMPLE_16STEREO ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_asynch_fg_rx_scb(struct snd_cs46xx * chip, char * scb_name, u32 dest,
                                   u16 hfg_scb_address,
                                   u16 asynch_buffer_address,
                                   struct dsp_scb_descriptor * parent_scb,
                                   int scb_child_type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;

	struct dsp_asynch_fg_rx_scb asynch_fg_rx_scb = {
		0xfe00,0x01ff,      /*  Prototype sample buffer size of 128 dwords */
		0x0064,0x001c,      /* Min Delta 7 dwords == 28 bytes */
		                    /* : Max delta 25 dwords == 100 bytes */
		0,hfg_scb_address,  /* Point to HFG task SCB */
		0,0,				/* Initialize current Delta and Consumer ptr adjustment count */
		{
			0,                /* Define the unused elements */
			0,
			0,
			0,
			0
		},
      
		0,0,
		0,dest,
    
		RSCONFIG_MODULO_128 |
        RSCONFIG_SAMPLE_16STEREO,                         /* Stereo, 128 dword */
		( (asynch_buffer_address + (16 * 4))  << 0x10),   /* This should be automagically 
							                                  synchrinized to the producer pointer */
    
		/* There is no correct initial value, it will depend upon the detected
		   rate etc  */
		0x18000000,         

		/* Set IEC958 input volume */
		0xffff - ins->spdif_input_volume_right,0xffff - ins->spdif_input_volume_left,
		0xffff - ins->spdif_input_volume_right,0xffff - ins->spdif_input_volume_left,
	};

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&asynch_fg_rx_scb,
					    dest,"ASYNCHFGRXCODE",parent_scb,
					    scb_child_type);

	return scb;
}