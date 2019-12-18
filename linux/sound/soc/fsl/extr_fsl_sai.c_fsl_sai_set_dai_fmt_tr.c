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
struct snd_soc_dai {int dummy; } ;
struct fsl_sai {int is_dsp_mode; int is_slave_mode; int /*<<< orphan*/  regmap; int /*<<< orphan*/  is_lsb_first; TYPE_1__* soc_data; } ;
struct TYPE_2__ {unsigned int reg_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int FSL_FMT_TRANSMITTER ; 
 int FSL_SAI_CR2_BCD_MSTR ; 
 int FSL_SAI_CR2_BCP ; 
 int FSL_SAI_CR4_FSD_MSTR ; 
 int FSL_SAI_CR4_FSE ; 
 int FSL_SAI_CR4_FSP ; 
 int FSL_SAI_CR4_MF ; 
 int /*<<< orphan*/  FSL_SAI_xCR2 (int,unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_xCR4 (int,unsigned int) ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_sai_set_dai_fmt_tr(struct snd_soc_dai *cpu_dai,
				unsigned int fmt, int fsl_dir)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned int ofs = sai->soc_data->reg_offset;
	bool tx = fsl_dir == FSL_FMT_TRANSMITTER;
	u32 val_cr2 = 0, val_cr4 = 0;

	if (!sai->is_lsb_first)
		val_cr4 |= FSL_SAI_CR4_MF;

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/*
		 * Frame low, 1clk before data, one word length for frame sync,
		 * frame sync starts one serial clock cycle earlier,
		 * that is, together with the last bit of the previous
		 * data word.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		val_cr4 |= FSL_SAI_CR4_FSE | FSL_SAI_CR4_FSP;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		/*
		 * Frame high, one word length for frame sync,
		 * frame sync asserts with the first bit of the frame.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/*
		 * Frame high, 1clk before data, one bit for frame sync,
		 * frame sync starts one serial clock cycle earlier,
		 * that is, together with the last bit of the previous
		 * data word.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		val_cr4 |= FSL_SAI_CR4_FSE;
		sai->is_dsp_mode = true;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		/*
		 * Frame high, one bit for frame sync,
		 * frame sync asserts with the first bit of the frame.
		 */
		val_cr2 |= FSL_SAI_CR2_BCP;
		sai->is_dsp_mode = true;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		/* To be done */
	default:
		return -EINVAL;
	}

	/* DAI clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		val_cr2 ^= FSL_SAI_CR2_BCP;
		val_cr4 ^= FSL_SAI_CR4_FSP;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		val_cr2 ^= FSL_SAI_CR2_BCP;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		val_cr4 ^= FSL_SAI_CR4_FSP;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		/* Nothing to do for both normal cases */
		break;
	default:
		return -EINVAL;
	}

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		val_cr2 |= FSL_SAI_CR2_BCD_MSTR;
		val_cr4 |= FSL_SAI_CR4_FSD_MSTR;
		sai->is_slave_mode = false;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		sai->is_slave_mode = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		val_cr2 |= FSL_SAI_CR2_BCD_MSTR;
		sai->is_slave_mode = false;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		val_cr4 |= FSL_SAI_CR4_FSD_MSTR;
		sai->is_slave_mode = true;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
			   FSL_SAI_CR2_BCP | FSL_SAI_CR2_BCD_MSTR, val_cr2);
	regmap_update_bits(sai->regmap, FSL_SAI_xCR4(tx, ofs),
			   FSL_SAI_CR4_MF | FSL_SAI_CR4_FSE |
			   FSL_SAI_CR4_FSP | FSL_SAI_CR4_FSD_MSTR, val_cr4);

	return 0;
}