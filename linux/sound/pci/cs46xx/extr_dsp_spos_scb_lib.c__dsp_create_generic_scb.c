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
struct dsp_symbol_entry {int address; } ;
struct dsp_spos_instance {struct dsp_scb_descriptor* the_null_scb; } ;
struct dsp_scb_descriptor {int address; char* scb_name; struct dsp_scb_descriptor* parent_scb_ptr; struct dsp_scb_descriptor* sub_list_ptr; struct dsp_scb_descriptor* next_scb_ptr; struct dsp_symbol_entry* task_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SCB_ON_PARENT_NEXT_SCB ; 
 int SCB_ON_PARENT_SUBLIST_SCB ; 
 size_t SCBfuncEntryPtr ; 
 size_t SCBsubListPtr ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_scb (struct snd_cs46xx*,char*,int*,int) ; 
 int /*<<< orphan*/  cs46xx_dsp_proc_register_scb_desc (struct snd_cs46xx*,struct dsp_scb_descriptor*) ; 
 int /*<<< orphan*/  cs46xx_dsp_spos_update_scb (struct snd_cs46xx*,struct dsp_scb_descriptor*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dsp_scb_descriptor * 
_dsp_create_generic_scb (struct snd_cs46xx *chip, char * name, u32 * scb_data, u32 dest,
                         struct dsp_symbol_entry * task_entry,
                         struct dsp_scb_descriptor * parent_scb,
                         int scb_child_type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;
  
	unsigned long flags;

	if (snd_BUG_ON(!ins->the_null_scb))
		return NULL;

	/* fill the data that will be wroten to DSP */
	scb_data[SCBsubListPtr] = 
		(ins->the_null_scb->address << 0x10) | ins->the_null_scb->address;

	scb_data[SCBfuncEntryPtr] &= 0xFFFF0000;
	scb_data[SCBfuncEntryPtr] |= task_entry->address;

	dev_dbg(chip->card->dev, "dsp_spos: creating SCB <%s>\n", name);

	scb = cs46xx_dsp_create_scb(chip,name,scb_data,dest);


	scb->sub_list_ptr = ins->the_null_scb;
	scb->next_scb_ptr = ins->the_null_scb;

	scb->parent_scb_ptr = parent_scb;
	scb->task_entry = task_entry;

  
	/* update parent SCB */
	if (scb->parent_scb_ptr) {
#if 0
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr = %s\n",
			scb->parent_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->next_scb_ptr = %s\n",
			scb->parent_scb_ptr->next_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->sub_list_ptr = %s\n",
			scb->parent_scb_ptr->sub_list_ptr->scb_name);
#endif
		/* link to  parent SCB */
		if (scb_child_type == SCB_ON_PARENT_NEXT_SCB) {
			if (snd_BUG_ON(scb->parent_scb_ptr->next_scb_ptr !=
				       ins->the_null_scb))
				return NULL;

			scb->parent_scb_ptr->next_scb_ptr = scb;

		} else if (scb_child_type == SCB_ON_PARENT_SUBLIST_SCB) {
			if (snd_BUG_ON(scb->parent_scb_ptr->sub_list_ptr !=
				       ins->the_null_scb))
				return NULL;

			scb->parent_scb_ptr->sub_list_ptr = scb;
		} else {
			snd_BUG();
		}

		spin_lock_irqsave(&chip->reg_lock, flags);

		/* update entry in DSP RAM */
		cs46xx_dsp_spos_update_scb(chip,scb->parent_scb_ptr);

		spin_unlock_irqrestore(&chip->reg_lock, flags);
	}


	cs46xx_dsp_proc_register_scb_desc (chip,scb);

	return scb;
}