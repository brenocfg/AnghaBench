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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  CLS_AB 131 
#define  CLS_H_HIFI 130 
#define  CLS_H_LP 129 
#define  CLS_H_NORMAL 128 
 int DAC_GAIN_0DB ; 
 int DAC_GAIN_M0P2DB ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_HPH ; 
 int WCD9XXX_A_ANA_HPH_PWR_LEVEL_LP ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_HPH_PWR_LEVEL_MASK ; 
 int WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL ; 
 int WCD9XXX_A_ANA_HPH_PWR_LEVEL_UHQA ; 
 int /*<<< orphan*/  WCD9XXX_CLASSH_CTRL_CCL_1 ; 
 int WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_30MA ; 
 int WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA ; 
 int /*<<< orphan*/  WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_MASK ; 
 int /*<<< orphan*/  WCD9XXX_CLASSH_CTRL_VCL_2 ; 
 int /*<<< orphan*/  WCD9XXX_CLASSH_CTRL_VCL_2_VREF_FILT_1_MASK ; 
 int WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_0KOHM ; 
 int WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_50KOHM ; 
 int /*<<< orphan*/  WCD9XXX_HPH_REFBUFF_UHQA_CTL ; 
 int /*<<< orphan*/  WCD9XXX_HPH_REFBUFF_UHQA_GAIN_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wcd_clsh_set_hph_mode(struct snd_soc_component *comp,
				  int mode)
{
	int val = 0, gain = 0, res_val;
	int ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;

	res_val = WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_0KOHM;
	switch (mode) {
	case CLS_H_NORMAL:
		res_val = WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_50KOHM;
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL;
		gain = DAC_GAIN_0DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		break;
	case CLS_AB:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL;
		gain = DAC_GAIN_0DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		break;
	case CLS_H_HIFI:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_UHQA;
		gain = DAC_GAIN_M0P2DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		break;
	case CLS_H_LP:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_LP;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_30MA;
		break;
	}

	snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_HPH,
					WCD9XXX_A_ANA_HPH_PWR_LEVEL_MASK, val);
	snd_soc_component_update_bits(comp, WCD9XXX_CLASSH_CTRL_VCL_2,
				WCD9XXX_CLASSH_CTRL_VCL_2_VREF_FILT_1_MASK,
				res_val);
	if (mode != CLS_H_LP)
		snd_soc_component_update_bits(comp,
					WCD9XXX_HPH_REFBUFF_UHQA_CTL,
					WCD9XXX_HPH_REFBUFF_UHQA_GAIN_MASK,
					gain);
	snd_soc_component_update_bits(comp, WCD9XXX_CLASSH_CTRL_CCL_1,
				WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_MASK,
				ipeak);
}