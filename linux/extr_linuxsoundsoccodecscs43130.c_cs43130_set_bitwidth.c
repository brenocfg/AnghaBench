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
struct regmap {int dummy; } ;
struct cs43130_bitwidth_map {int ch_bit; int sp_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS43130_ASP_BITSIZE_MASK ; 
 int /*<<< orphan*/  CS43130_ASP_CH_1_SZ_EN ; 
 int /*<<< orphan*/  CS43130_ASP_CH_2_SZ_EN ; 
#define  CS43130_ASP_DOP_DAI 130 
#define  CS43130_ASP_PCM_DAI 129 
 int /*<<< orphan*/  CS43130_CH_BITSIZE_MASK ; 
 int /*<<< orphan*/  CS43130_SP_BITSIZE ; 
 int /*<<< orphan*/  CS43130_XSP_BITSIZE_MASK ; 
 int CS43130_XSP_BITSIZE_SHIFT ; 
 int /*<<< orphan*/  CS43130_XSP_CH_1_SZ_EN ; 
 int /*<<< orphan*/  CS43130_XSP_CH_2_SZ_EN ; 
#define  CS43130_XSP_DOP_DAI 128 
 int EINVAL ; 
 struct cs43130_bitwidth_map* cs43130_get_bitwidth_table (unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs43130_set_bitwidth(int dai_id, unsigned int bitwidth_dai,
			  struct regmap *regmap)
{
	const struct cs43130_bitwidth_map *bw_map;

	bw_map = cs43130_get_bitwidth_table(bitwidth_dai);
	if (!bw_map)
		return -EINVAL;

	switch (dai_id) {
	case CS43130_ASP_PCM_DAI:
	case CS43130_ASP_DOP_DAI:
		regmap_update_bits(regmap, CS43130_ASP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_ASP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_SP_BITSIZE,
				   CS43130_ASP_BITSIZE_MASK, bw_map->sp_bit);
		break;
	case CS43130_XSP_DOP_DAI:
		regmap_update_bits(regmap, CS43130_XSP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_XSP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_SP_BITSIZE,
				   CS43130_XSP_BITSIZE_MASK, bw_map->sp_bit <<
				   CS43130_XSP_BITSIZE_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}