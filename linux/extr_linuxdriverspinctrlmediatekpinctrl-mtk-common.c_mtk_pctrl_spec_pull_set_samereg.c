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
struct mtk_pin_spec_pupd_set_samereg {unsigned int pin; unsigned char offset; int /*<<< orphan*/  r1_bit; int /*<<< orphan*/  r0_bit; int /*<<< orphan*/  pupd_bit; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  MTK_PUPD_SET_R1R0_00 131 
#define  MTK_PUPD_SET_R1R0_01 130 
#define  MTK_PUPD_SET_R1R0_10 129 
#define  MTK_PUPD_SET_R1R0_11 128 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,unsigned int) ; 

int mtk_pctrl_spec_pull_set_samereg(struct regmap *regmap,
		const struct mtk_pin_spec_pupd_set_samereg *pupd_infos,
		unsigned int info_num, unsigned int pin,
		unsigned char align, bool isup, unsigned int r1r0)
{
	unsigned int i;
	unsigned int reg_pupd, reg_set, reg_rst;
	unsigned int bit_pupd, bit_r0, bit_r1;
	const struct mtk_pin_spec_pupd_set_samereg *spec_pupd_pin;
	bool find = false;

	for (i = 0; i < info_num; i++) {
		if (pin == pupd_infos[i].pin) {
			find = true;
			break;
		}
	}

	if (!find)
		return -EINVAL;

	spec_pupd_pin = pupd_infos + i;
	reg_set = spec_pupd_pin->offset + align;
	reg_rst = spec_pupd_pin->offset + (align << 1);

	if (isup)
		reg_pupd = reg_rst;
	else
		reg_pupd = reg_set;

	bit_pupd = BIT(spec_pupd_pin->pupd_bit);
	regmap_write(regmap, reg_pupd, bit_pupd);

	bit_r0 = BIT(spec_pupd_pin->r0_bit);
	bit_r1 = BIT(spec_pupd_pin->r1_bit);

	switch (r1r0) {
	case MTK_PUPD_SET_R1R0_00:
		regmap_write(regmap, reg_rst, bit_r0);
		regmap_write(regmap, reg_rst, bit_r1);
		break;
	case MTK_PUPD_SET_R1R0_01:
		regmap_write(regmap, reg_set, bit_r0);
		regmap_write(regmap, reg_rst, bit_r1);
		break;
	case MTK_PUPD_SET_R1R0_10:
		regmap_write(regmap, reg_rst, bit_r0);
		regmap_write(regmap, reg_set, bit_r1);
		break;
	case MTK_PUPD_SET_R1R0_11:
		regmap_write(regmap, reg_set, bit_r0);
		regmap_write(regmap, reg_set, bit_r1);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}