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
struct snd_cs46xx {TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int nscb; int scb_highest_frag_index; struct dsp_scb_descriptor* scbs; } ;
struct dsp_scb_descriptor {int index; int ref_count; int /*<<< orphan*/  scb_symbol; int /*<<< orphan*/  address; int /*<<< orphan*/  scb_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSP_MAX_SCB_DESC ; 
 int /*<<< orphan*/  SYMBOL_PARAMETER ; 
 int /*<<< orphan*/  add_symbol (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int find_free_scb_index (struct dsp_spos_instance*) ; 
 int /*<<< orphan*/  memset (struct dsp_scb_descriptor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dsp_scb_descriptor * _map_scb (struct snd_cs46xx *chip, char * name, u32 dest)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * desc = NULL;
	int index;

	if (ins->nscb == DSP_MAX_SCB_DESC - 1) {
		dev_err(chip->card->dev,
			"dsp_spos: got no place for other SCB\n");
		return NULL;
	}

	index = find_free_scb_index (ins);

	memset(&ins->scbs[index], 0, sizeof(ins->scbs[index]));
	strcpy(ins->scbs[index].scb_name, name);
	ins->scbs[index].address = dest;
	ins->scbs[index].index = index;
	ins->scbs[index].ref_count = 1;

	desc = (ins->scbs + index);
	ins->scbs[index].scb_symbol = add_symbol (chip, name, dest, SYMBOL_PARAMETER);

	if (index > ins->scb_highest_frag_index)
		ins->scb_highest_frag_index = index;

	if (index == ins->nscb)
		ins->nscb++;

	return desc;
}