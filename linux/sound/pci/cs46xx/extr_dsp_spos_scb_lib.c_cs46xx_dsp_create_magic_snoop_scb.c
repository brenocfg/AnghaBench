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
struct dsp_scb_descriptor {int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; } ;
struct dsp_magic_snoop_task {int member_2; int member_15; TYPE_1__ member_17; int /*<<< orphan*/  member_16; scalar_t__ member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ RSCONFIG_MODULO_64 ; 
 scalar_t__ RSCONFIG_SAMPLE_16STEREO ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dsp_scb_descriptor*,int) ; 

struct dsp_scb_descriptor *
cs46xx_dsp_create_magic_snoop_scb(struct snd_cs46xx * chip, char * scb_name, u32 dest,
				  u16 snoop_buffer_address,
				  struct dsp_scb_descriptor * snoop_scb,
				  struct dsp_scb_descriptor * parent_scb,
				  int scb_child_type)
{
	struct dsp_scb_descriptor * scb;
  
	struct dsp_magic_snoop_task magic_snoop_scb = {
		/* 0 */ 0, /* i0 */
		/* 1 */ 0, /* i1 */
		/* 2 */ snoop_buffer_address << 0x10,
		/* 3 */ 0,snoop_scb->address,
		/* 4 */ 0, /* i3 */
		/* 5 */ 0, /* i4 */
		/* 6 */ 0, /* i5 */
		/* 7 */ 0, /* i6 */
		/* 8 */ 0, /* i7 */
		/* 9 */ 0,0, /* next_scb, sub_list_ptr */
		/* A */ 0,0, /* entry_point, this_ptr */
		/* B */ RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,
		/* C */ snoop_buffer_address  << 0x10,
		/* D */ 0,
		/* E */ { 0x8000,0x8000,
	        /* F */   0xffff,0xffff
		}
	};

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&magic_snoop_scb,
					    dest,"MAGICSNOOPTASK",parent_scb,
					    scb_child_type);

	return scb;
}