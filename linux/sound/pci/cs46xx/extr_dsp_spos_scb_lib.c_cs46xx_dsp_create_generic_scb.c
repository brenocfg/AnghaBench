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
struct snd_cs46xx {TYPE_1__* card; } ;
struct dsp_symbol_entry {int dummy; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_CODE ; 
 struct dsp_scb_descriptor* _dsp_create_generic_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dsp_symbol_entry*,struct dsp_scb_descriptor*,int) ; 
 struct dsp_symbol_entry* cs46xx_dsp_lookup_symbol (struct snd_cs46xx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct dsp_scb_descriptor * 
cs46xx_dsp_create_generic_scb (struct snd_cs46xx *chip, char * name, u32 * scb_data,
			       u32 dest, char * task_entry_name,
                               struct dsp_scb_descriptor * parent_scb,
                               int scb_child_type)
{
	struct dsp_symbol_entry * task_entry;

	task_entry = cs46xx_dsp_lookup_symbol (chip,task_entry_name,
					       SYMBOL_CODE);
  
	if (task_entry == NULL) {
		dev_err(chip->card->dev,
			"dsp_spos: symbol %s not found\n", task_entry_name);
		return NULL;
	}
  
	return _dsp_create_generic_scb (chip,name,scb_data,dest,task_entry,
					parent_scb,scb_child_type);
}