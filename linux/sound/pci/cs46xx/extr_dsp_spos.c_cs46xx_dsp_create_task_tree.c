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
struct dsp_task_descriptor {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dsp_create_task_tree (struct snd_cs46xx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct dsp_task_descriptor* _map_task_tree (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dsp_task_descriptor *
cs46xx_dsp_create_task_tree (struct snd_cs46xx *chip, char * name, u32 * task_data,
			     u32 dest, int size)
{
	struct dsp_task_descriptor * desc;

	desc = _map_task_tree (chip,name,dest,size);
	if (desc) {
		desc->data = task_data;
		_dsp_create_task_tree(chip,task_data,dest,size);
	} else {
		dev_err(chip->card->dev, "dsp_spos: failed to map TASK\n");
	}

	return desc;
}