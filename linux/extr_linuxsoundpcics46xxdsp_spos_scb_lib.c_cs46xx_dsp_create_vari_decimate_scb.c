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
typedef  int u16 ;
struct snd_cs46xx {int dummy; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; } ;
struct dsp_vari_decimate_scb {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_11; int member_13; int member_20; int member_21; TYPE_1__ member_22; scalar_t__ member_19; int /*<<< orphan*/  member_18; int /*<<< orphan*/  member_17; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_12; scalar_t__ member_10; } ;
struct dsp_scb_descriptor {int dummy; } ;

/* Variables and functions */
 scalar_t__ RSCONFIG_MODULO_256 ; 
 scalar_t__ RSCONFIG_MODULO_8 ; 
 scalar_t__ RSCONFIG_SAMPLE_16STEREO ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor * 
cs46xx_dsp_create_vari_decimate_scb(struct snd_cs46xx * chip,char * scb_name,
                                    u16 vari_buffer_addr0,
                                    u16 vari_buffer_addr1,
                                    u32 dest,
                                    struct dsp_scb_descriptor * parent_scb,
                                    int scb_child_type)
{

	struct dsp_scb_descriptor * scb;
  
	struct dsp_vari_decimate_scb vari_decimate_scb = {
		0x0028,0x00c8,
		0x5555,0x0000,
		0x0000,0x0000,
		vari_buffer_addr0,vari_buffer_addr1,
    
		0x0028,0x00c8,
		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_256, 
    
		0xFF800000,   
		0,
		0x0080,vari_buffer_addr1 + (25 * 4), 
    
		0,0, 
		0,0,

		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_8,
		vari_buffer_addr0 << 0x10,   
		0x04000000,                   
		{
			0x8000,0x8000, 
			0xFFFF,0xFFFF
		}
	};

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&vari_decimate_scb,
					    dest,"VARIDECIMATE",parent_scb,
					    scb_child_type);
  
	return scb;
}