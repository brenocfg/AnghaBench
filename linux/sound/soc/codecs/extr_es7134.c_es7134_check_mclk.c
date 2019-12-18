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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct es7134_data {unsigned int mclk; TYPE_1__* chip; } ;
struct es7134_clock_mode {unsigned int rate_min; unsigned int rate_max; int mclk_fs_num; unsigned int* mclk_fs; } ;
struct TYPE_2__ {int mode_num; struct es7134_clock_mode* modes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

__attribute__((used)) static int es7134_check_mclk(struct snd_soc_dai *dai,
			     struct es7134_data *priv,
			     unsigned int rate)
{
	unsigned int mfs = priv->mclk / rate;
	int i, j;

	for (i = 0; i < priv->chip->mode_num; i++) {
		const struct es7134_clock_mode *mode = &priv->chip->modes[i];

		if (rate < mode->rate_min || rate > mode->rate_max)
			continue;

		for (j = 0; j < mode->mclk_fs_num; j++) {
			if (mode->mclk_fs[j] == mfs)
				return 0;
		}

		dev_err(dai->dev, "unsupported mclk_fs %u for rate %u\n",
			mfs, rate);
		return -EINVAL;
	}

	/* should not happen */
	dev_err(dai->dev, "unsupported rate: %u\n", rate);
	return -EINVAL;
}