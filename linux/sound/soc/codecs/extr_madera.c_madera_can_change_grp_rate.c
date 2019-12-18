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
struct madera_priv {int* domain_group_ref; TYPE_1__* madera; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  MADERA_AIF1_RATE_CTRL 169 
#define  MADERA_AIF2_RATE_CTRL 168 
#define  MADERA_AIF3_RATE_CTRL 167 
#define  MADERA_AIF4_RATE_CTRL 166 
#define  MADERA_ASRC1_RATE1 165 
#define  MADERA_ASRC1_RATE2 164 
#define  MADERA_ASRC2_RATE1 163 
#define  MADERA_ASRC2_RATE2 162 
 size_t MADERA_DOM_GRP_AIF1 ; 
 size_t MADERA_DOM_GRP_AIF2 ; 
 size_t MADERA_DOM_GRP_AIF3 ; 
 size_t MADERA_DOM_GRP_AIF4 ; 
 size_t MADERA_DOM_GRP_ASRC1 ; 
 size_t MADERA_DOM_GRP_ASRC2 ; 
 size_t MADERA_DOM_GRP_DSP1 ; 
 size_t MADERA_DOM_GRP_DSP2 ; 
 size_t MADERA_DOM_GRP_DSP3 ; 
 size_t MADERA_DOM_GRP_DSP4 ; 
 size_t MADERA_DOM_GRP_DSP5 ; 
 size_t MADERA_DOM_GRP_DSP6 ; 
 size_t MADERA_DOM_GRP_DSP7 ; 
 size_t MADERA_DOM_GRP_FX ; 
 size_t MADERA_DOM_GRP_ISRC1 ; 
 size_t MADERA_DOM_GRP_ISRC2 ; 
 size_t MADERA_DOM_GRP_ISRC3 ; 
 size_t MADERA_DOM_GRP_ISRC4 ; 
 size_t MADERA_DOM_GRP_OUT ; 
 size_t MADERA_DOM_GRP_PWM ; 
 size_t MADERA_DOM_GRP_SLIMBUS ; 
 size_t MADERA_DOM_GRP_SPD ; 
#define  MADERA_DSP1_CONFIG_1 161 
#define  MADERA_DSP1_CONFIG_2 160 
#define  MADERA_DSP2_CONFIG_1 159 
#define  MADERA_DSP2_CONFIG_2 158 
#define  MADERA_DSP3_CONFIG_1 157 
#define  MADERA_DSP3_CONFIG_2 156 
#define  MADERA_DSP4_CONFIG_1 155 
#define  MADERA_DSP4_CONFIG_2 154 
#define  MADERA_DSP5_CONFIG_1 153 
#define  MADERA_DSP5_CONFIG_2 152 
#define  MADERA_DSP6_CONFIG_1 151 
#define  MADERA_DSP6_CONFIG_2 150 
#define  MADERA_DSP7_CONFIG_1 149 
#define  MADERA_DSP7_CONFIG_2 148 
#define  MADERA_FX_CTRL1 147 
#define  MADERA_ISRC_1_CTRL_1 146 
#define  MADERA_ISRC_1_CTRL_2 145 
#define  MADERA_ISRC_2_CTRL_1 144 
#define  MADERA_ISRC_2_CTRL_2 143 
#define  MADERA_ISRC_3_CTRL_1 142 
#define  MADERA_ISRC_3_CTRL_2 141 
#define  MADERA_ISRC_4_CTRL_1 140 
#define  MADERA_ISRC_4_CTRL_2 139 
#define  MADERA_OUTPUT_RATE_1 138 
#define  MADERA_PWM_DRIVE_1 137 
#define  MADERA_SLIMBUS_RATES_1 136 
#define  MADERA_SLIMBUS_RATES_2 135 
#define  MADERA_SLIMBUS_RATES_3 134 
#define  MADERA_SLIMBUS_RATES_4 133 
#define  MADERA_SLIMBUS_RATES_5 132 
#define  MADERA_SLIMBUS_RATES_6 131 
#define  MADERA_SLIMBUS_RATES_7 130 
#define  MADERA_SLIMBUS_RATES_8 129 
#define  MADERA_SPD1_TX_CONTROL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 

__attribute__((used)) static bool madera_can_change_grp_rate(const struct madera_priv *priv,
				       unsigned int reg)
{
	int count;

	switch (reg) {
	case MADERA_FX_CTRL1:
		count = priv->domain_group_ref[MADERA_DOM_GRP_FX];
		break;
	case MADERA_ASRC1_RATE1:
	case MADERA_ASRC1_RATE2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ASRC1];
		break;
	case MADERA_ASRC2_RATE1:
	case MADERA_ASRC2_RATE2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ASRC2];
		break;
	case MADERA_ISRC_1_CTRL_1:
	case MADERA_ISRC_1_CTRL_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ISRC1];
		break;
	case MADERA_ISRC_2_CTRL_1:
	case MADERA_ISRC_2_CTRL_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ISRC2];
		break;
	case MADERA_ISRC_3_CTRL_1:
	case MADERA_ISRC_3_CTRL_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ISRC3];
		break;
	case MADERA_ISRC_4_CTRL_1:
	case MADERA_ISRC_4_CTRL_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_ISRC4];
		break;
	case MADERA_OUTPUT_RATE_1:
		count = priv->domain_group_ref[MADERA_DOM_GRP_OUT];
		break;
	case MADERA_SPD1_TX_CONTROL:
		count = priv->domain_group_ref[MADERA_DOM_GRP_SPD];
		break;
	case MADERA_DSP1_CONFIG_1:
	case MADERA_DSP1_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP1];
		break;
	case MADERA_DSP2_CONFIG_1:
	case MADERA_DSP2_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP2];
		break;
	case MADERA_DSP3_CONFIG_1:
	case MADERA_DSP3_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP3];
		break;
	case MADERA_DSP4_CONFIG_1:
	case MADERA_DSP4_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP4];
		break;
	case MADERA_DSP5_CONFIG_1:
	case MADERA_DSP5_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP5];
		break;
	case MADERA_DSP6_CONFIG_1:
	case MADERA_DSP6_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP6];
		break;
	case MADERA_DSP7_CONFIG_1:
	case MADERA_DSP7_CONFIG_2:
		count = priv->domain_group_ref[MADERA_DOM_GRP_DSP7];
		break;
	case MADERA_AIF1_RATE_CTRL:
		count = priv->domain_group_ref[MADERA_DOM_GRP_AIF1];
		break;
	case MADERA_AIF2_RATE_CTRL:
		count = priv->domain_group_ref[MADERA_DOM_GRP_AIF2];
		break;
	case MADERA_AIF3_RATE_CTRL:
		count = priv->domain_group_ref[MADERA_DOM_GRP_AIF3];
		break;
	case MADERA_AIF4_RATE_CTRL:
		count = priv->domain_group_ref[MADERA_DOM_GRP_AIF4];
		break;
	case MADERA_SLIMBUS_RATES_1:
	case MADERA_SLIMBUS_RATES_2:
	case MADERA_SLIMBUS_RATES_3:
	case MADERA_SLIMBUS_RATES_4:
	case MADERA_SLIMBUS_RATES_5:
	case MADERA_SLIMBUS_RATES_6:
	case MADERA_SLIMBUS_RATES_7:
	case MADERA_SLIMBUS_RATES_8:
		count = priv->domain_group_ref[MADERA_DOM_GRP_SLIMBUS];
		break;
	case MADERA_PWM_DRIVE_1:
		count = priv->domain_group_ref[MADERA_DOM_GRP_PWM];
		break;
	default:
		return false;
	}

	dev_dbg(priv->madera->dev, "Rate reg 0x%x group ref %d\n", reg, count);

	if (count)
		return false;
	else
		return true;
}