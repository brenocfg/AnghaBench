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
struct dsp_scb_descriptor {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCB_BYTES ; 
 int /*<<< orphan*/  _dsp_create_scb (struct snd_cs46xx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dsp_scb_descriptor* _map_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dsp_scb_descriptor *
cs46xx_dsp_create_scb (struct snd_cs46xx *chip, char * name, u32 * scb_data, u32 dest)
{
	struct dsp_scb_descriptor * desc;

#ifdef CONFIG_PM_SLEEP
	/* copy the data for resume */
	scb_data = kmemdup(scb_data, SCB_BYTES, GFP_KERNEL);
	if (!scb_data)
		return NULL;
#endif

	desc = _map_scb (chip,name,dest);
	if (desc) {
		desc->data = scb_data;
		_dsp_create_scb(chip,scb_data,dest);
	} else {
		dev_err(chip->card->dev, "dsp_spos: failed to map SCB\n");
#ifdef CONFIG_PM_SLEEP
		kfree(scb_data);
#endif
	}

	return desc;
}