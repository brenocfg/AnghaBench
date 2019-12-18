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
struct rk_pdm_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PDM_CKP_INVERTED ; 
 unsigned int PDM_CKP_MSK ; 
 unsigned int PDM_CKP_NORMAL ; 
 int /*<<< orphan*/  PDM_CLK_CTRL ; 
#define  SND_SOC_DAIFMT_IB_NF 129 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct rk_pdm_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_pdm_set_fmt(struct snd_soc_dai *cpu_dai,
				unsigned int fmt)
{
	struct rk_pdm_dev *pdm = to_info(cpu_dai);
	unsigned int mask = 0, val = 0;

	mask = PDM_CKP_MSK;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		val = PDM_CKP_NORMAL;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		val = PDM_CKP_INVERTED;
		break;
	default:
		return -EINVAL;
	}

	pm_runtime_get_sync(cpu_dai->dev);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, mask, val);
	pm_runtime_put(cpu_dai->dev);

	return 0;
}