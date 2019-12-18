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
struct snd_cs46xx {TYPE_1__* card; } ;
struct dsp_segment_desc {int offset; int size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSP_PARAMETER_BYTE_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_cs46xx_download (struct snd_cs46xx*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dsp_load_parameter(struct snd_cs46xx *chip,
			      struct dsp_segment_desc *parameter)
{
	u32 doffset, dsize;

	if (!parameter) {
		dev_dbg(chip->card->dev,
			"dsp_spos: module got no parameter segment\n");
		return 0;
	}

	doffset = (parameter->offset * 4 + DSP_PARAMETER_BYTE_OFFSET);
	dsize   = parameter->size * 4;

	dev_dbg(chip->card->dev,
		"dsp_spos: downloading parameter data to chip (%08x-%08x)\n",
		    doffset,doffset + dsize);
	if (snd_cs46xx_download (chip, parameter->data, doffset, dsize)) {
		dev_err(chip->card->dev,
			"dsp_spos: failed to download parameter data to DSP\n");
		return -EINVAL;
	}
	return 0;
}