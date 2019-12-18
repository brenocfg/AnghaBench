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
typedef  unsigned int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct fsl_esai {unsigned int* hck_rate; int* hck_dir; int* sck_div; int /*<<< orphan*/  regmap; struct clk* extalclk; scalar_t__ synchronous; struct clk* fsysclk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ESAI_ECR_ERI ; 
 unsigned int ESAI_ECR_ERO ; 
 unsigned int ESAI_ECR_ETI ; 
 unsigned int ESAI_ECR_ETO ; 
#define  ESAI_HCKR_EXTAL 131 
#define  ESAI_HCKR_FSYS 130 
#define  ESAI_HCKT_EXTAL 129 
#define  ESAI_HCKT_FSYS 128 
 unsigned int ESAI_xCCR_xHCKD ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  REG_ESAI_ECR ; 
 int /*<<< orphan*/  REG_ESAI_xCCR (int) ; 
 int SND_SOC_CLOCK_IN ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int fsl_esai_divisor_cal (struct snd_soc_dai*,int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				   unsigned int freq, int dir)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	struct clk *clksrc = esai_priv->extalclk;
	bool tx = (clk_id <= ESAI_HCKT_EXTAL || esai_priv->synchronous);
	bool in = dir == SND_SOC_CLOCK_IN;
	u32 ratio, ecr = 0;
	unsigned long clk_rate;
	int ret;

	if (freq == 0) {
		dev_err(dai->dev, "%sput freq of HCK%c should not be 0Hz\n",
			in ? "in" : "out", tx ? 'T' : 'R');
		return -EINVAL;
	}

	/* Bypass divider settings if the requirement doesn't change */
	if (freq == esai_priv->hck_rate[tx] && dir == esai_priv->hck_dir[tx])
		return 0;

	/* sck_div can be only bypassed if ETO/ERO=0 and SNC_SOC_CLOCK_OUT */
	esai_priv->sck_div[tx] = true;

	/* Set the direction of HCKT/HCKR pins */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xHCKD, in ? 0 : ESAI_xCCR_xHCKD);

	if (in)
		goto out;

	switch (clk_id) {
	case ESAI_HCKT_FSYS:
	case ESAI_HCKR_FSYS:
		clksrc = esai_priv->fsysclk;
		break;
	case ESAI_HCKT_EXTAL:
		ecr |= ESAI_ECR_ETI;
		break;
	case ESAI_HCKR_EXTAL:
		ecr |= esai_priv->synchronous ? ESAI_ECR_ETI : ESAI_ECR_ERI;
		break;
	default:
		return -EINVAL;
	}

	if (IS_ERR(clksrc)) {
		dev_err(dai->dev, "no assigned %s clock\n",
				clk_id % 2 ? "extal" : "fsys");
		return PTR_ERR(clksrc);
	}
	clk_rate = clk_get_rate(clksrc);

	ratio = clk_rate / freq;
	if (ratio * freq > clk_rate)
		ret = ratio * freq - clk_rate;
	else if (ratio * freq < clk_rate)
		ret = clk_rate - ratio * freq;
	else
		ret = 0;

	/* Block if clock source can not be divided into the required rate */
	if (ret != 0 && clk_rate / ret < 1000) {
		dev_err(dai->dev, "failed to derive required HCK%c rate\n",
				tx ? 'T' : 'R');
		return -EINVAL;
	}

	/* Only EXTAL source can be output directly without using PSR and PM */
	if (ratio == 1 && clksrc == esai_priv->extalclk) {
		/* Bypass all the dividers if not being needed */
		ecr |= tx ? ESAI_ECR_ETO : ESAI_ECR_ERO;
		goto out;
	} else if (ratio < 2) {
		/* The ratio should be no less than 2 if using other sources */
		dev_err(dai->dev, "failed to derive required HCK%c rate\n",
				tx ? 'T' : 'R');
		return -EINVAL;
	}

	ret = fsl_esai_divisor_cal(dai, tx, ratio, false, 0);
	if (ret)
		return ret;

	esai_priv->sck_div[tx] = false;

out:
	esai_priv->hck_dir[tx] = dir;
	esai_priv->hck_rate[tx] = freq;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
			   tx ? ESAI_ECR_ETI | ESAI_ECR_ETO :
			   ESAI_ECR_ERI | ESAI_ECR_ERO, ecr);

	return 0;
}