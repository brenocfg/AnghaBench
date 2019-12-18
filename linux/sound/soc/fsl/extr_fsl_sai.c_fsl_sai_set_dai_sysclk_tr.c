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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct fsl_sai {int /*<<< orphan*/  regmap; TYPE_1__* soc_data; } ;
struct TYPE_2__ {unsigned int reg_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int FSL_FMT_TRANSMITTER ; 
#define  FSL_SAI_CLK_BUS 131 
#define  FSL_SAI_CLK_MAST1 130 
#define  FSL_SAI_CLK_MAST2 129 
#define  FSL_SAI_CLK_MAST3 128 
 int /*<<< orphan*/  FSL_SAI_CR2_MSEL_BUS ; 
 int /*<<< orphan*/  FSL_SAI_CR2_MSEL_MASK ; 
 int /*<<< orphan*/  FSL_SAI_CR2_MSEL_MCLK1 ; 
 int /*<<< orphan*/  FSL_SAI_CR2_MSEL_MCLK2 ; 
 int /*<<< orphan*/  FSL_SAI_CR2_MSEL_MCLK3 ; 
 int /*<<< orphan*/  FSL_SAI_xCR2 (int,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_sai_set_dai_sysclk_tr(struct snd_soc_dai *cpu_dai,
		int clk_id, unsigned int freq, int fsl_dir)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned int ofs = sai->soc_data->reg_offset;
	bool tx = fsl_dir == FSL_FMT_TRANSMITTER;
	u32 val_cr2 = 0;

	switch (clk_id) {
	case FSL_SAI_CLK_BUS:
		val_cr2 |= FSL_SAI_CR2_MSEL_BUS;
		break;
	case FSL_SAI_CLK_MAST1:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK1;
		break;
	case FSL_SAI_CLK_MAST2:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK2;
		break;
	case FSL_SAI_CLK_MAST3:
		val_cr2 |= FSL_SAI_CR2_MSEL_MCLK3;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(sai->regmap, FSL_SAI_xCR2(tx, ofs),
			   FSL_SAI_CR2_MSEL_MASK, val_cr2);

	return 0;
}