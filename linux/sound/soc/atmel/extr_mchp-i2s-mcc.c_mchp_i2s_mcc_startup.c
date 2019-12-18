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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct mchp_i2s_mcc_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHP_I2SMCC_CR ; 
 int /*<<< orphan*/  MCHP_I2SMCC_CR_SWRST ; 
 int /*<<< orphan*/  mchp_i2s_mcc_is_running (struct mchp_i2s_mcc_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mchp_i2s_mcc_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mchp_i2s_mcc_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	/* Software reset the IP if it's not running */
	if (!mchp_i2s_mcc_is_running(dev)) {
		return regmap_write(dev->regmap, MCHP_I2SMCC_CR,
				    MCHP_I2SMCC_CR_SWRST);
	}

	return 0;
}