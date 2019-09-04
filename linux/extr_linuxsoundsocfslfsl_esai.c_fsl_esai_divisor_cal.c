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
struct fsl_esai {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESAI_xCCR_xFP (int) ; 
 int ESAI_xCCR_xFP_MASK ; 
 int ESAI_xCCR_xPM (int) ; 
 int ESAI_xCCR_xPM_MASK ; 
 int ESAI_xCCR_xPSR_BYPASS ; 
 int ESAI_xCCR_xPSR_DIV8 ; 
 int ESAI_xCCR_xPSR_MASK ; 
 int /*<<< orphan*/  REG_ESAI_xCCR (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_divisor_cal(struct snd_soc_dai *dai, bool tx, u32 ratio,
				bool usefp, u32 fp)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 psr, pm = 999, maxfp, prod, sub, savesub, i, j;

	maxfp = usefp ? 16 : 1;

	if (usefp && fp)
		goto out_fp;

	if (ratio > 2 * 8 * 256 * maxfp || ratio < 2) {
		dev_err(dai->dev, "the ratio is out of range (2 ~ %d)\n",
				2 * 8 * 256 * maxfp);
		return -EINVAL;
	} else if (ratio % 2) {
		dev_err(dai->dev, "the raio must be even if using upper divider\n");
		return -EINVAL;
	}

	ratio /= 2;

	psr = ratio <= 256 * maxfp ? ESAI_xCCR_xPSR_BYPASS : ESAI_xCCR_xPSR_DIV8;

	/* Do not loop-search if PM (1 ~ 256) alone can serve the ratio */
	if (ratio <= 256) {
		pm = ratio;
		fp = 1;
		goto out;
	}

	/* Set the max fluctuation -- 0.1% of the max devisor */
	savesub = (psr ? 1 : 8)  * 256 * maxfp / 1000;

	/* Find the best value for PM */
	for (i = 1; i <= 256; i++) {
		for (j = 1; j <= maxfp; j++) {
			/* PSR (1 or 8) * PM (1 ~ 256) * FP (1 ~ 16) */
			prod = (psr ? 1 : 8) * i * j;

			if (prod == ratio)
				sub = 0;
			else if (prod / ratio == 1)
				sub = prod - ratio;
			else if (ratio / prod == 1)
				sub = ratio - prod;
			else
				continue;

			/* Calculate the fraction */
			sub = sub * 1000 / ratio;
			if (sub < savesub) {
				savesub = sub;
				pm = i;
				fp = j;
			}

			/* We are lucky */
			if (savesub == 0)
				goto out;
		}
	}

	if (pm == 999) {
		dev_err(dai->dev, "failed to calculate proper divisors\n");
		return -EINVAL;
	}

out:
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xPSR_MASK | ESAI_xCCR_xPM_MASK,
			   psr | ESAI_xCCR_xPM(pm));

out_fp:
	/* Bypass fp if not being required */
	if (maxfp <= 1)
		return 0;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xFP_MASK, ESAI_xCCR_xFP(fp));

	return 0;
}