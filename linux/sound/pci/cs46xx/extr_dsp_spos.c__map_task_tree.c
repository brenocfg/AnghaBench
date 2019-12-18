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
typedef  void* u32 ;
struct snd_cs46xx {TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_task_descriptor {size_t index; void* size; void* address; int /*<<< orphan*/  task_name; } ;
struct dsp_spos_instance {int ntask; struct dsp_task_descriptor* tasks; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSP_MAX_TASK_DESC ; 
 int /*<<< orphan*/  SYMBOL_PARAMETER ; 
 int /*<<< orphan*/  add_symbol (struct snd_cs46xx*,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dsp_task_descriptor *
_map_task_tree (struct snd_cs46xx *chip, char * name, u32 dest, u32 size)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_task_descriptor * desc = NULL;

	if (ins->ntask == DSP_MAX_TASK_DESC - 1) {
		dev_err(chip->card->dev,
			"dsp_spos: got no place for other TASK\n");
		return NULL;
	}

	if (name)
		strcpy(ins->tasks[ins->ntask].task_name, name);
	else
		strcpy(ins->tasks[ins->ntask].task_name, "(NULL)");
	ins->tasks[ins->ntask].address = dest;
	ins->tasks[ins->ntask].size = size;

	/* quick find in list */
	ins->tasks[ins->ntask].index = ins->ntask;
	desc = (ins->tasks + ins->ntask);
	ins->ntask++;

	if (name)
		add_symbol (chip,name,dest,SYMBOL_PARAMETER);
	return desc;
}