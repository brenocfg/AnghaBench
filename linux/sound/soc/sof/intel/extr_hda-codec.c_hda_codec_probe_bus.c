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
struct hdac_bus {int codec_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HDA_MAX_CODECS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int hda_codec_probe (struct snd_sof_dev*,int) ; 
 struct hdac_bus* sof_to_bus (struct snd_sof_dev*) ; 

int hda_codec_probe_bus(struct snd_sof_dev *sdev)
{
	struct hdac_bus *bus = sof_to_bus(sdev);
	int i, ret;

	/* probe codecs in avail slots */
	for (i = 0; i < HDA_MAX_CODECS; i++) {

		if (!(bus->codec_mask & (1 << i)))
			continue;

		ret = hda_codec_probe(sdev, i);
		if (ret < 0) {
			dev_err(bus->dev, "error: codec #%d probe error, ret: %d\n",
				i, ret);
			return ret;
		}
	}

	return 0;
}