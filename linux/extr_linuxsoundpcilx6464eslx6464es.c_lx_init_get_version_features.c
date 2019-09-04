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
struct lx6464es {int board_sample_rate; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int lx_dsp_get_clock_frequency (struct lx6464es*,int*) ; 
 int lx_dsp_get_version (struct lx6464es*,int*) ; 

__attribute__((used)) static int lx_init_get_version_features(struct lx6464es *chip)
{
	u32 dsp_version;

	int err;

	dev_dbg(chip->card->dev, "->lx_init_get_version_features\n");

	err = lx_dsp_get_version(chip, &dsp_version);

	if (err == 0) {
		u32 freq;

		dev_info(chip->card->dev, "DSP version: V%02d.%02d #%d\n",
			   (dsp_version>>16) & 0xff, (dsp_version>>8) & 0xff,
			   dsp_version & 0xff);

		/* later: what firmware version do we expect? */

		/* retrieve Play/Rec features */
		/* done here because we may have to handle alternate
		 * DSP files. */
		/* later */

		/* init the EtherSound sample rate */
		err = lx_dsp_get_clock_frequency(chip, &freq);
		if (err == 0)
			chip->board_sample_rate = freq;
		dev_dbg(chip->card->dev, "actual clock frequency %d\n", freq);
	} else {
		dev_err(chip->card->dev, "DSP corrupted \n");
		err = -EAGAIN;
	}

	return err;
}