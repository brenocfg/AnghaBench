#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int rx_pause_start_pos; int rx_pause_cycles; int tx_pause_start_pos; int tx_pause_cycles; } ;
union cx2072x_reg_i2spcm_ctrl_reg6 {int ulval; TYPE_6__ r; } ;
struct TYPE_8__ {int i2s_pcm_clk_div_chan_en; scalar_t__ i2s_pcm_clk_div; } ;
union cx2072x_reg_i2spcm_ctrl_reg5 {int ulval; TYPE_2__ r; } ;
union cx2072x_reg_i2spcm_ctrl_reg4 {int ulval; } ;
struct TYPE_11__ {int rx_master; int rx_endian_sel; int rx_dstart_dly; int rx_slot_2; scalar_t__ rx_slot_1; } ;
union cx2072x_reg_i2spcm_ctrl_reg3 {int /*<<< orphan*/  ulval; TYPE_5__ r; } ;
struct TYPE_10__ {int tx_master; int tx_endian_sel; int tx_dstart_dly; int tx_slot_2; scalar_t__ tx_slot_1; } ;
union cx2072x_reg_i2spcm_ctrl_reg2 {int /*<<< orphan*/  ulval; TYPE_4__ r; } ;
struct TYPE_9__ {int rx_data_one_line; int tx_data_one_line; int rx_ws_pol; int rx_ws_wid; int rx_frm_len; int rx_sa_size; int tx_ws_pol; int tx_ws_wid; int tx_frm_len; int tx_sa_size; } ;
union cx2072x_reg_i2spcm_ctrl_reg1 {int ulval; TYPE_3__ r; } ;
struct TYPE_7__ {int i2s_bclk_invert; } ;
union cx2072x_reg_digital_bios_test2 {int ulval; TYPE_1__ r; } ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct cx2072x_priv {int frame_size; int sample_size; unsigned int dai_fmt; int sample_rate; int /*<<< orphan*/  regmap; scalar_t__ en_aec_ref; struct device* dev; } ;

/* Variables and functions */
 int BITS_PER_SLOT ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_BIOS_TEST2 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL1 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL2 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL3 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL4 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL5 ; 
 int /*<<< orphan*/  CX2072X_I2SPCM_CONTROL6 ; 
 int EINVAL ; 
 scalar_t__ PLL_OUT_HZ_48 ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
 unsigned int const SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int const SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int const SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 unsigned int do_div (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx2072x_config_i2spcm(struct cx2072x_priv *cx2072x)
{
	struct device *dev = cx2072x->dev;
	unsigned int bclk_rate = 0;
	int is_i2s = 0;
	int has_one_bit_delay = 0;
	int is_frame_inv = 0;
	int is_bclk_inv = 0;
	int pulse_len;
	int frame_len = cx2072x->frame_size;
	int sample_size = cx2072x->sample_size;
	int i2s_right_slot;
	int i2s_right_pause_interval = 0;
	int i2s_right_pause_pos;
	int is_big_endian = 1;
	u64 div;
	unsigned int mod;
	union cx2072x_reg_i2spcm_ctrl_reg1 reg1;
	union cx2072x_reg_i2spcm_ctrl_reg2 reg2;
	union cx2072x_reg_i2spcm_ctrl_reg3 reg3;
	union cx2072x_reg_i2spcm_ctrl_reg4 reg4;
	union cx2072x_reg_i2spcm_ctrl_reg5 reg5;
	union cx2072x_reg_i2spcm_ctrl_reg6 reg6;
	union cx2072x_reg_digital_bios_test2 regdbt2;
	const unsigned int fmt = cx2072x->dai_fmt;

	if (frame_len <= 0) {
		dev_err(dev, "Incorrect frame len %d\n", frame_len);
		return -EINVAL;
	}

	if (sample_size <= 0) {
		dev_err(dev, "Incorrect sample size %d\n", sample_size);
		return -EINVAL;
	}

	dev_dbg(dev, "config_i2spcm set_dai_fmt- %08x\n", fmt);

	regdbt2.ulval = 0xac;

	/* set master/slave */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		reg2.r.tx_master = 1;
		reg3.r.rx_master = 1;
		dev_dbg(dev, "Sets Master mode\n");
		break;

	case SND_SOC_DAIFMT_CBS_CFS:
		reg2.r.tx_master = 0;
		reg3.r.rx_master = 0;
		dev_dbg(dev, "Sets Slave mode\n");
		break;

	default:
		dev_err(dev, "Unsupported DAI master mode\n");
		return -EINVAL;
	}

	/* set format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		is_i2s = 1;
		has_one_bit_delay = 1;
		pulse_len = frame_len / 2;
		break;

	case SND_SOC_DAIFMT_RIGHT_J:
		is_i2s = 1;
		pulse_len = frame_len / 2;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		is_i2s = 1;
		pulse_len = frame_len / 2;
		break;

	default:
		dev_err(dev, "Unsupported DAI format\n");
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		is_frame_inv = is_i2s;
		is_bclk_inv = is_i2s;
		break;

	case SND_SOC_DAIFMT_IB_IF:
		is_frame_inv = !is_i2s;
		is_bclk_inv = !is_i2s;
		break;

	case SND_SOC_DAIFMT_IB_NF:
		is_frame_inv = is_i2s;
		is_bclk_inv = !is_i2s;
		break;

	case SND_SOC_DAIFMT_NB_IF:
		is_frame_inv = !is_i2s;
		is_bclk_inv = is_i2s;
		break;

	default:
		dev_err(dev, "Unsupported DAI clock inversion\n");
		return -EINVAL;
	}

	reg1.r.rx_data_one_line = 1;
	reg1.r.tx_data_one_line = 1;

	if (is_i2s) {
		i2s_right_slot = (frame_len / 2) / BITS_PER_SLOT;
		i2s_right_pause_interval = (frame_len / 2) % BITS_PER_SLOT;
		i2s_right_pause_pos = i2s_right_slot * BITS_PER_SLOT;
	}

	reg1.r.rx_ws_pol = is_frame_inv;
	reg1.r.rx_ws_wid = pulse_len - 1;

	reg1.r.rx_frm_len = frame_len / BITS_PER_SLOT - 1;
	reg1.r.rx_sa_size = (sample_size / BITS_PER_SLOT) - 1;

	reg1.r.tx_ws_pol = reg1.r.rx_ws_pol;
	reg1.r.tx_ws_wid = pulse_len - 1;
	reg1.r.tx_frm_len = reg1.r.rx_frm_len;
	reg1.r.tx_sa_size = reg1.r.rx_sa_size;

	reg2.r.tx_endian_sel = !is_big_endian;
	reg2.r.tx_dstart_dly = has_one_bit_delay;
	if (cx2072x->en_aec_ref)
		reg2.r.tx_dstart_dly = 0;

	reg3.r.rx_endian_sel = !is_big_endian;
	reg3.r.rx_dstart_dly = has_one_bit_delay;

	reg4.ulval = 0;

	if (is_i2s) {
		reg2.r.tx_slot_1 = 0;
		reg2.r.tx_slot_2 = i2s_right_slot;
		reg3.r.rx_slot_1 = 0;
		if (cx2072x->en_aec_ref)
			reg3.r.rx_slot_2 = 0;
		else
			reg3.r.rx_slot_2 = i2s_right_slot;
		reg6.r.rx_pause_start_pos = i2s_right_pause_pos;
		reg6.r.rx_pause_cycles = i2s_right_pause_interval;
		reg6.r.tx_pause_start_pos = i2s_right_pause_pos;
		reg6.r.tx_pause_cycles = i2s_right_pause_interval;
	} else {
		dev_err(dev, "TDM mode is not implemented yet\n");
		return -EINVAL;
	}
	regdbt2.r.i2s_bclk_invert = is_bclk_inv;

	reg1.r.rx_data_one_line = 1;
	reg1.r.tx_data_one_line = 1;

	/* Configures the BCLK output */
	bclk_rate = cx2072x->sample_rate * frame_len;
	reg5.r.i2s_pcm_clk_div_chan_en = 0;

	/* Disables bclk output before setting new value */
	regmap_write(cx2072x->regmap, CX2072X_I2SPCM_CONTROL5, 0);

	if (reg2.r.tx_master) {
		/* Configures BCLK rate */
		div = PLL_OUT_HZ_48;
		mod = do_div(div, bclk_rate);
		if (mod) {
			dev_err(dev, "Unsupported BCLK %dHz\n", bclk_rate);
			return -EINVAL;
		}
		dev_dbg(dev, "enables BCLK %dHz output\n", bclk_rate);
		reg5.r.i2s_pcm_clk_div = (u32)div - 1;
		reg5.r.i2s_pcm_clk_div_chan_en = 1;
	}

	regmap_write(cx2072x->regmap, CX2072X_I2SPCM_CONTROL1, reg1.ulval);
	regmap_update_bits(cx2072x->regmap, CX2072X_I2SPCM_CONTROL2, 0xffffffc0,
			   reg2.ulval);
	regmap_update_bits(cx2072x->regmap, CX2072X_I2SPCM_CONTROL3, 0xffffffc0,
			   reg3.ulval);
	regmap_write(cx2072x->regmap, CX2072X_I2SPCM_CONTROL4, reg4.ulval);
	regmap_write(cx2072x->regmap, CX2072X_I2SPCM_CONTROL6, reg6.ulval);
	regmap_write(cx2072x->regmap, CX2072X_I2SPCM_CONTROL5, reg5.ulval);

	regmap_write(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST2,
		     regdbt2.ulval);

	return 0;
}