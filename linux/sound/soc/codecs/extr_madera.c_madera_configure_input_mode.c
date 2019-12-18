#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** inmode; unsigned int* dmic_ref; } ;
struct TYPE_4__ {TYPE_1__ codec; } ;
struct madera {int type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_2__ pdata; } ;

/* Variables and functions */
#define  CS47L15 135 
#define  CS47L35 134 
#define  CS47L85 133 
#define  CS47L90 132 
#define  CS47L91 131 
 scalar_t__ MADERA_ADC_DIGITAL_VOLUME_1L ; 
 scalar_t__ MADERA_ADC_DIGITAL_VOLUME_1R ; 
 scalar_t__ MADERA_IN1L_CONTROL ; 
 int /*<<< orphan*/  MADERA_IN1L_SRC_SE_MASK ; 
 int MADERA_IN1L_SRC_SE_SHIFT ; 
 int /*<<< orphan*/  MADERA_IN1R_SRC_SE_MASK ; 
 int MADERA_IN1R_SRC_SE_SHIFT ; 
 int /*<<< orphan*/  MADERA_IN1_DMIC_SUP_MASK ; 
 unsigned int MADERA_IN1_DMIC_SUP_SHIFT ; 
#define  MADERA_INMODE_DIFF 130 
#define  MADERA_INMODE_SE 129 
#define  WM1840 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void madera_configure_input_mode(struct madera *madera)
{
	unsigned int dig_mode, ana_mode_l, ana_mode_r;
	int max_analogue_inputs, max_dmic_sup, i;

	switch (madera->type) {
	case CS47L15:
		max_analogue_inputs = 1;
		max_dmic_sup = 2;
		break;
	case CS47L35:
		max_analogue_inputs = 2;
		max_dmic_sup = 2;
		break;
	case CS47L85:
	case WM1840:
		max_analogue_inputs = 3;
		max_dmic_sup = 3;
		break;
	case CS47L90:
	case CS47L91:
		max_analogue_inputs = 2;
		max_dmic_sup = 2;
		break;
	default:
		max_analogue_inputs = 2;
		max_dmic_sup = 4;
		break;
	}

	/*
	 * Initialize input modes from the A settings. For muxed inputs the
	 * B settings will be applied if the mux is changed
	 */
	for (i = 0; i < max_dmic_sup; i++) {
		dev_dbg(madera->dev, "IN%d mode %u:%u:%u:%u\n", i + 1,
			madera->pdata.codec.inmode[i][0],
			madera->pdata.codec.inmode[i][1],
			madera->pdata.codec.inmode[i][2],
			madera->pdata.codec.inmode[i][3]);

		dig_mode = madera->pdata.codec.dmic_ref[i] <<
			   MADERA_IN1_DMIC_SUP_SHIFT;

		switch (madera->pdata.codec.inmode[i][0]) {
		case MADERA_INMODE_DIFF:
			ana_mode_l = 0;
			break;
		case MADERA_INMODE_SE:
			ana_mode_l = 1 << MADERA_IN1L_SRC_SE_SHIFT;
			break;
		default:
			dev_warn(madera->dev,
				 "IN%dAL Illegal inmode %u ignored\n",
				 i + 1, madera->pdata.codec.inmode[i][0]);
			continue;
		}

		switch (madera->pdata.codec.inmode[i][1]) {
		case MADERA_INMODE_DIFF:
			ana_mode_r = 0;
			break;
		case MADERA_INMODE_SE:
			ana_mode_r = 1 << MADERA_IN1R_SRC_SE_SHIFT;
			break;
		default:
			dev_warn(madera->dev,
				 "IN%dAR Illegal inmode %u ignored\n",
				 i + 1, madera->pdata.codec.inmode[i][1]);
			continue;
		}

		dev_dbg(madera->dev,
			"IN%dA DMIC mode=0x%x Analogue mode=0x%x,0x%x\n",
			i + 1, dig_mode, ana_mode_l, ana_mode_r);

		regmap_update_bits(madera->regmap,
				   MADERA_IN1L_CONTROL + (i * 8),
				   MADERA_IN1_DMIC_SUP_MASK, dig_mode);

		if (i >= max_analogue_inputs)
			continue;

		regmap_update_bits(madera->regmap,
				   MADERA_ADC_DIGITAL_VOLUME_1L + (i * 8),
				   MADERA_IN1L_SRC_SE_MASK, ana_mode_l);

		regmap_update_bits(madera->regmap,
				   MADERA_ADC_DIGITAL_VOLUME_1R + (i * 8),
				   MADERA_IN1R_SRC_SE_MASK, ana_mode_r);
	}
}