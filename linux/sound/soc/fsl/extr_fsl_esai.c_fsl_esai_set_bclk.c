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
typedef  int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct fsl_esai {int* hck_rate; int* sck_rate; scalar_t__* sck_div; scalar_t__ slave_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int fsl_esai_divisor_cal (struct snd_soc_dai*,int,int,int,int) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_set_bclk(struct snd_soc_dai *dai, bool tx, u32 freq)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 hck_rate = esai_priv->hck_rate[tx];
	u32 sub, ratio = hck_rate / freq;
	int ret;

	/* Don't apply for fully slave mode or unchanged bclk */
	if (esai_priv->slave_mode || esai_priv->sck_rate[tx] == freq)
		return 0;

	if (ratio * freq > hck_rate)
		sub = ratio * freq - hck_rate;
	else if (ratio * freq < hck_rate)
		sub = hck_rate - ratio * freq;
	else
		sub = 0;

	/* Block if clock source can not be divided into the required rate */
	if (sub != 0 && hck_rate / sub < 1000) {
		dev_err(dai->dev, "failed to derive required SCK%c rate\n",
				tx ? 'T' : 'R');
		return -EINVAL;
	}

	/* The ratio should be contented by FP alone if bypassing PM and PSR */
	if (!esai_priv->sck_div[tx] && (ratio > 16 || ratio == 0)) {
		dev_err(dai->dev, "the ratio is out of range (1 ~ 16)\n");
		return -EINVAL;
	}

	ret = fsl_esai_divisor_cal(dai, tx, ratio, true,
			esai_priv->sck_div[tx] ? 0 : ratio);
	if (ret)
		return ret;

	/* Save current bclk rate */
	esai_priv->sck_rate[tx] = freq;

	return 0;
}