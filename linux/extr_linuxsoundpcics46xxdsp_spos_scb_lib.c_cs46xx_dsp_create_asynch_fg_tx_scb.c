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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct snd_cs46xx {int dummy; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_asynch_fg_tx_scb {int member_0; int member_1; int member_2; int member_3; int member_5; int member_10; int member_17; int member_18; int member_19; int member_20; int member_21; int member_22; scalar_t__ member_16; scalar_t__ member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; TYPE_1__ member_11; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_4; } ;

/* Variables and functions */
 scalar_t__ AFGTxAccumPhi ; 
 scalar_t__ RSCONFIG_MODULO_256 ; 
 scalar_t__ RSCONFIG_SAMPLE_16STEREO ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,scalar_t__*,scalar_t__,char*,struct dsp_scb_descriptor*,int) ; 

__attribute__((used)) static struct dsp_scb_descriptor * 
cs46xx_dsp_create_asynch_fg_tx_scb(struct snd_cs46xx * chip, char * scb_name, u32 dest,
                                   u16 hfg_scb_address,
                                   u16 asynch_buffer_address,
                                   struct dsp_scb_descriptor * parent_scb,
                                   int scb_child_type)
{

	struct dsp_scb_descriptor * scb;

	struct dsp_asynch_fg_tx_scb asynch_fg_tx_scb = {
		0xfc00,0x03ff,      /*  Prototype sample buffer size of 256 dwords */
		0x0058,0x0028,      /* Min Delta 7 dwords == 28 bytes */
		/* : Max delta 25 dwords == 100 bytes */
		0,hfg_scb_address,  /* Point to HFG task SCB */
		0,0,		    /* Initialize current Delta and Consumer ptr adjustment count */
		0,                  /* Initialize accumulated Phi to 0 */
		0,0x2aab,           /* Const 1/3 */
    
		{
			0,         /* Define the unused elements */
			0,
			0
		},
    
		0,0,
		0,dest + AFGTxAccumPhi,
    
		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_256, /* Stereo, 256 dword */
		(asynch_buffer_address) << 0x10,  /* This should be automagically synchronized
                                                     to the producer pointer */
    
		/* There is no correct initial value, it will depend upon the detected
		   rate etc  */
		0x18000000,                     /* Phi increment for approx 32k operation */
		0x8000,0x8000,                  /* Volume controls are unused at this time */
		0x8000,0x8000
	};
  
	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&asynch_fg_tx_scb,
					    dest,"ASYNCHFGTXCODE",parent_scb,
					    scb_child_type);

	return scb;
}