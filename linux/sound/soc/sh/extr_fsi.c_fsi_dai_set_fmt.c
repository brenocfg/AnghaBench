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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct fsi_priv {int clk_master; int bit_clk_inv; int lr_clk_inv; scalar_t__ clk_cpg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  fsi_clk_init (int /*<<< orphan*/ ,struct fsi_priv*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_clk_set_rate_cpg ; 
 int /*<<< orphan*/  fsi_clk_set_rate_external ; 
 struct fsi_priv* fsi_get_priv_frm_dai (struct snd_soc_dai*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 
 scalar_t__ fsi_is_spdif (struct fsi_priv*) ; 
 int fsi_set_fmt_dai (struct fsi_priv*,unsigned int) ; 
 int fsi_set_fmt_spdif (struct fsi_priv*) ; 

__attribute__((used)) static int fsi_dai_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct fsi_priv *fsi = fsi_get_priv_frm_dai(dai);
	int ret;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		fsi->clk_master = 1; /* codec is slave, cpu is master */
		break;
	default:
		return -EINVAL;
	}

	/* set clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		fsi->bit_clk_inv = 0;
		fsi->lr_clk_inv = 1;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		fsi->bit_clk_inv = 1;
		fsi->lr_clk_inv = 0;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		fsi->bit_clk_inv = 1;
		fsi->lr_clk_inv = 1;
		break;
	case SND_SOC_DAIFMT_NB_NF:
	default:
		fsi->bit_clk_inv = 0;
		fsi->lr_clk_inv = 0;
		break;
	}

	if (fsi_is_clk_master(fsi)) {
		if (fsi->clk_cpg)
			fsi_clk_init(dai->dev, fsi, 0, 1, 1,
				     fsi_clk_set_rate_cpg);
		else
			fsi_clk_init(dai->dev, fsi, 1, 1, 0,
				     fsi_clk_set_rate_external);
	}

	/* set format */
	if (fsi_is_spdif(fsi))
		ret = fsi_set_fmt_spdif(fsi);
	else
		ret = fsi_set_fmt_dai(fsi, fmt & SND_SOC_DAIFMT_FORMAT_MASK);

	return ret;
}