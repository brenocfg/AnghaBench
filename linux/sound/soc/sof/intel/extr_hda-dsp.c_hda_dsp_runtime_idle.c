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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct hdac_bus {scalar_t__ codec_powered; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct hdac_bus* sof_to_bus (struct snd_sof_dev*) ; 

int hda_dsp_runtime_idle(struct snd_sof_dev *sdev)
{
	struct hdac_bus *hbus = sof_to_bus(sdev);

	if (hbus->codec_powered) {
		dev_dbg(sdev->dev, "some codecs still powered (%08X), not idle\n",
			(unsigned int)hbus->codec_powered);
		return -EBUSY;
	}

	return 0;
}