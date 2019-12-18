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
struct snd_cs46xx {int /*<<< orphan*/  reg_lock; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int nscb; scalar_t__ the_null_scb; size_t scb_highest_frag_index; struct dsp_scb_descriptor* scbs; } ;
struct dsp_scb_descriptor {int index; scalar_t__ sub_list_ptr; scalar_t__ next_scb_ptr; int deleted; int /*<<< orphan*/ * data; int /*<<< orphan*/  scb_symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dsp_unlink_scb (struct snd_cs46xx*,struct dsp_scb_descriptor*) ; 
 int /*<<< orphan*/  cs46xx_dsp_proc_free_scb_desc (struct dsp_scb_descriptor*) ; 
 int i ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_symbol (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cs46xx_dsp_remove_scb (struct snd_cs46xx *chip, struct dsp_scb_descriptor * scb)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	unsigned long flags;

	/* check integrety */
	if (snd_BUG_ON(scb->index < 0 ||
		       scb->index >= ins->nscb ||
		       (ins->scbs + scb->index) != scb))
		return;

#if 0
	/* can't remove a SCB with childs before 
	   removing childs first  */
	if (snd_BUG_ON(scb->sub_list_ptr != ins->the_null_scb ||
		       scb->next_scb_ptr != ins->the_null_scb))
		goto _end;
#endif

	spin_lock_irqsave(&chip->reg_lock, flags);    
	_dsp_unlink_scb (chip,scb);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	cs46xx_dsp_proc_free_scb_desc(scb);
	if (snd_BUG_ON(!scb->scb_symbol))
		return;
	remove_symbol (chip,scb->scb_symbol);

	ins->scbs[scb->index].deleted = 1;
#ifdef CONFIG_PM_SLEEP
	kfree(ins->scbs[scb->index].data);
	ins->scbs[scb->index].data = NULL;
#endif

	if (scb->index < ins->scb_highest_frag_index)
		ins->scb_highest_frag_index = scb->index;

	if (scb->index == ins->nscb - 1) {
		ins->nscb --;
	}

	if (ins->scb_highest_frag_index > ins->nscb) {
		ins->scb_highest_frag_index = ins->nscb;
	}

#if 0
	/* !!!! THIS IS A PIECE OF SHIT MADE BY ME !!! */
	for(i = scb->index + 1;i < ins->nscb; ++i) {
		ins->scbs[i - 1].index = i - 1;
	}
#endif
}