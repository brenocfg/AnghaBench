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
typedef  int /*<<< orphan*/  u16 ;
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {scalar_t__ the_null_scb; struct dsp_scb_descriptor* record_mixer_scb; } ;
struct dsp_scb_descriptor {scalar_t__ sub_list_ptr; } ;

/* Variables and functions */
 int SCB_ON_PARENT_NEXT_SCB ; 
 int SCB_ON_PARENT_SUBLIST_SCB ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_pcm_serial_input_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,struct dsp_scb_descriptor*,struct dsp_scb_descriptor*,int) ; 
 struct dsp_scb_descriptor* find_next_free_scb (struct snd_cs46xx*,scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 

struct dsp_scb_descriptor *
cs46xx_add_record_source (struct snd_cs46xx *chip, struct dsp_scb_descriptor * source,
			  u16 addr, char * scb_name)
{
  	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * parent;
	struct dsp_scb_descriptor * pcm_input;
	int insert_point;

	if (snd_BUG_ON(!ins->record_mixer_scb))
		return NULL;

	if (ins->record_mixer_scb->sub_list_ptr != ins->the_null_scb) {
		parent = find_next_free_scb (chip,ins->record_mixer_scb->sub_list_ptr);
		insert_point = SCB_ON_PARENT_NEXT_SCB;
	} else {
		parent = ins->record_mixer_scb;
		insert_point = SCB_ON_PARENT_SUBLIST_SCB;
	}

	pcm_input = cs46xx_dsp_create_pcm_serial_input_scb(chip,scb_name,addr,
							   source, parent,
							   insert_point);

	return pcm_input;
}