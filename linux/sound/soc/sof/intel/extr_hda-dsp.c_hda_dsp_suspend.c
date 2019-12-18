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
struct snd_sof_dev {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hda_suspend (struct snd_sof_dev*,int) ; 
 struct hdac_bus* sof_to_bus (struct snd_sof_dev*) ; 

int hda_dsp_suspend(struct snd_sof_dev *sdev)
{
	struct hdac_bus *bus = sof_to_bus(sdev);
	int ret;

	/* stop hda controller and power dsp off */
	ret = hda_suspend(sdev, false);
	if (ret < 0) {
		dev_err(bus->dev, "error: suspending dsp\n");
		return ret;
	}

	return 0;
}