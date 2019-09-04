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
struct rk_i2s_dev {int is_master_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2S_CKR ; 
 unsigned int I2S_CKR_CKP_MASK ; 
 unsigned int I2S_CKR_CKP_NEG ; 
 unsigned int I2S_CKR_CKP_POS ; 
 unsigned int I2S_CKR_MSS_MASK ; 
 unsigned int I2S_CKR_MSS_MASTER ; 
 unsigned int I2S_CKR_MSS_SLAVE ; 
 int /*<<< orphan*/  I2S_RXCR ; 
 unsigned int I2S_RXCR_IBM_LSJM ; 
 unsigned int I2S_RXCR_IBM_MASK ; 
 unsigned int I2S_RXCR_IBM_NORMAL ; 
 unsigned int I2S_RXCR_IBM_RSJM ; 
 unsigned int I2S_RXCR_PBM_MASK ; 
 unsigned int I2S_RXCR_PBM_MODE (int) ; 
 unsigned int I2S_RXCR_TFS_MASK ; 
 unsigned int I2S_RXCR_TFS_PCM ; 
 int /*<<< orphan*/  I2S_TXCR ; 
 unsigned int I2S_TXCR_IBM_LSJM ; 
 unsigned int I2S_TXCR_IBM_MASK ; 
 unsigned int I2S_TXCR_IBM_NORMAL ; 
 unsigned int I2S_TXCR_IBM_RSJM ; 
 unsigned int I2S_TXCR_PBM_MASK ; 
 unsigned int I2S_TXCR_PBM_MODE (int) ; 
 unsigned int I2S_TXCR_TFS_MASK ; 
 unsigned int I2S_TXCR_TFS_PCM ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
#define  SND_SOC_DAIFMT_DSP_A 134 
#define  SND_SOC_DAIFMT_DSP_B 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct rk_i2s_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_i2s_set_fmt(struct snd_soc_dai *cpu_dai,
				unsigned int fmt)
{
	struct rk_i2s_dev *i2s = to_info(cpu_dai);
	unsigned int mask = 0, val = 0;

	mask = I2S_CKR_MSS_MASK;
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* Set source clock in Master mode */
		val = I2S_CKR_MSS_MASTER;
		i2s->is_master_mode = true;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		val = I2S_CKR_MSS_SLAVE;
		i2s->is_master_mode = false;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, I2S_CKR, mask, val);

	mask = I2S_CKR_CKP_MASK;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		val = I2S_CKR_CKP_NEG;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		val = I2S_CKR_CKP_POS;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, I2S_CKR, mask, val);

	mask = I2S_TXCR_IBM_MASK | I2S_TXCR_TFS_MASK | I2S_TXCR_PBM_MASK;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_RIGHT_J:
		val = I2S_TXCR_IBM_RSJM;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = I2S_TXCR_IBM_LSJM;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = I2S_TXCR_IBM_NORMAL;
		break;
	case SND_SOC_DAIFMT_DSP_A: /* PCM no delay mode */
		val = I2S_TXCR_TFS_PCM;
		break;
	case SND_SOC_DAIFMT_DSP_B: /* PCM delay 1 mode */
		val = I2S_TXCR_TFS_PCM | I2S_TXCR_PBM_MODE(1);
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, I2S_TXCR, mask, val);

	mask = I2S_RXCR_IBM_MASK | I2S_RXCR_TFS_MASK | I2S_RXCR_PBM_MASK;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_RIGHT_J:
		val = I2S_RXCR_IBM_RSJM;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = I2S_RXCR_IBM_LSJM;
		break;
	case SND_SOC_DAIFMT_I2S:
		val = I2S_RXCR_IBM_NORMAL;
		break;
	case SND_SOC_DAIFMT_DSP_A: /* PCM no delay mode */
		val = I2S_RXCR_TFS_PCM;
		break;
	case SND_SOC_DAIFMT_DSP_B: /* PCM delay 1 mode */
		val = I2S_RXCR_TFS_PCM | I2S_RXCR_PBM_MODE(1);
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, I2S_RXCR, mask, val);

	return 0;
}