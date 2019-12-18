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
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int bst_vctl; int bst_vctl_sel; int bst_ipk; int temp_warn_thld; int irq_drv_sel; int irq_gpio_sel; scalar_t__ boost_ind; scalar_t__ vmon_pol_inv; scalar_t__ imon_pol_inv; scalar_t__ multi_amp_mode; scalar_t__ amp_pcm_inv; scalar_t__ dcm_mode; } ;
struct cs35l36_private {scalar_t__ rev_id; scalar_t__ chip_version; int /*<<< orphan*/  regmap; TYPE_1__ pdata; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CS35L35_BSTCVRT_CTL_MASK ; 
 int CS35L35_BSTCVRT_CTL_SEL_MASK ; 
 scalar_t__ CS35L36_10V_L36 ; 
 int /*<<< orphan*/  CS35L36_AMP_DIG_VOL_CTRL ; 
 int CS35L36_AMP_PCM_INV_MASK ; 
 int CS35L36_ASP_TX_HIZ_MASK ; 
 int /*<<< orphan*/  CS35L36_ASP_TX_PIN_CTRL ; 
 int /*<<< orphan*/  CS35L36_BSTCVRT_DCM_CTRL ; 
 int /*<<< orphan*/  CS35L36_BSTCVRT_OVERVOLT_CTRL ; 
 int /*<<< orphan*/  CS35L36_BSTCVRT_PEAK_CUR ; 
 int /*<<< orphan*/  CS35L36_BSTCVRT_VCTRL1 ; 
 int /*<<< orphan*/  CS35L36_BSTCVRT_VCTRL2 ; 
 int /*<<< orphan*/  CS35L36_BST_ANA2_TEST ; 
 int CS35L36_BST_CTRL_10V_CLAMP ; 
 int CS35L36_BST_CTRL_LIM_MASK ; 
 int CS35L36_BST_CTRL_LIM_SHIFT ; 
 int CS35L36_BST_IPK_MASK ; 
 int CS35L36_BST_MAN_IPKCOMP_EN_MASK ; 
 int CS35L36_BST_MAN_IPKCOMP_MASK ; 
 int CS35L36_BST_MAN_IPKCOMP_SHIFT ; 
 int CS35L36_BST_OVP_THLD_11V ; 
 int CS35L36_BST_OVP_THLD_MASK ; 
 int CS35L36_BST_OVP_TRIM_11V ; 
 int CS35L36_BST_OVP_TRIM_MASK ; 
 int CS35L36_BST_OVP_TRIM_SHIFT ; 
 int /*<<< orphan*/  CS35L36_BST_TST_MANUAL ; 
 int /*<<< orphan*/  CS35L36_CTRL_OVRRIDE ; 
 int CS35L36_DCM_AUTO_MASK ; 
 int /*<<< orphan*/  CS35L36_DTEMP_WARN_THLD ; 
 int CS35L36_IMON_POL_MASK ; 
 int CS35L36_INT_DRV_SEL_MASK ; 
 int CS35L36_INT_DRV_SEL_SHIFT ; 
 int CS35L36_INT_GPIO_SEL_MASK ; 
 int CS35L36_INT_GPIO_SEL_SHIFT ; 
 int /*<<< orphan*/  CS35L36_PAD_INTERFACE ; 
 scalar_t__ CS35L36_REV_A0 ; 
 int CS35L36_SYNC_GLOBAL_OVR_MASK ; 
 int CS35L36_SYNC_GLOBAL_OVR_SHIFT ; 
 int CS35L36_TEMP_THLD_MASK ; 
 int /*<<< orphan*/  CS35L36_TESTKEY_CTRL ; 
 int /*<<< orphan*/  CS35L36_TEST_LOCK1 ; 
 int /*<<< orphan*/  CS35L36_TEST_LOCK2 ; 
 int /*<<< orphan*/  CS35L36_TEST_UNLOCK1 ; 
 int /*<<< orphan*/  CS35L36_TEST_UNLOCK2 ; 
 int /*<<< orphan*/  CS35L36_VI_SPKMON_FILT ; 
 int CS35L36_VMON_POL_MASK ; 
 int cs35l36_boost_inductor (struct cs35l36_private*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l36_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l36_component_probe(struct snd_soc_component *component)
{
	struct cs35l36_private *cs35l36 =
			snd_soc_component_get_drvdata(component);
	int ret = 0;

	if ((cs35l36->rev_id == CS35L36_REV_A0) && cs35l36->pdata.dcm_mode) {
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_DCM_CTRL,
				   CS35L36_DCM_AUTO_MASK,
				   CS35L36_DCM_AUTO_MASK);

		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK1);
		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK2);

		regmap_update_bits(cs35l36->regmap, CS35L36_BST_TST_MANUAL,
				   CS35L36_BST_MAN_IPKCOMP_MASK,
				   0 << CS35L36_BST_MAN_IPKCOMP_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BST_TST_MANUAL,
				   CS35L36_BST_MAN_IPKCOMP_EN_MASK,
				   CS35L36_BST_MAN_IPKCOMP_EN_MASK);

		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
				CS35L36_TEST_LOCK1);
		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
				CS35L36_TEST_LOCK2);
	}

	if (cs35l36->pdata.amp_pcm_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_DIG_VOL_CTRL,
				   CS35L36_AMP_PCM_INV_MASK,
				   CS35L36_AMP_PCM_INV_MASK);

	if (cs35l36->pdata.multi_amp_mode)
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_TX_PIN_CTRL,
				   CS35L36_ASP_TX_HIZ_MASK,
				   CS35L36_ASP_TX_HIZ_MASK);

	if (cs35l36->pdata.imon_pol_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_VI_SPKMON_FILT,
				   CS35L36_IMON_POL_MASK, 0);

	if (cs35l36->pdata.vmon_pol_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_VI_SPKMON_FILT,
				   CS35L36_VMON_POL_MASK, 0);

	if (cs35l36->pdata.bst_vctl)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL1,
				   CS35L35_BSTCVRT_CTL_MASK,
				   cs35l36->pdata.bst_vctl);

	if (cs35l36->pdata.bst_vctl_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL2,
				   CS35L35_BSTCVRT_CTL_SEL_MASK,
				   cs35l36->pdata.bst_vctl_sel);

	if (cs35l36->pdata.bst_ipk)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_PEAK_CUR,
				   CS35L36_BST_IPK_MASK,
				   cs35l36->pdata.bst_ipk);

	if (cs35l36->pdata.boost_ind) {
		ret = cs35l36_boost_inductor(cs35l36, cs35l36->pdata.boost_ind);
		if (ret < 0) {
			dev_err(cs35l36->dev,
				"Boost inductor config failed(%d)\n", ret);
			return ret;
		}
	}

	if (cs35l36->pdata.temp_warn_thld)
		regmap_update_bits(cs35l36->regmap, CS35L36_DTEMP_WARN_THLD,
				   CS35L36_TEMP_THLD_MASK,
				   cs35l36->pdata.temp_warn_thld);

	if (cs35l36->pdata.irq_drv_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
				   CS35L36_INT_DRV_SEL_MASK,
				   cs35l36->pdata.irq_drv_sel <<
				   CS35L36_INT_DRV_SEL_SHIFT);

	if (cs35l36->pdata.irq_gpio_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
				   CS35L36_INT_GPIO_SEL_MASK,
				   cs35l36->pdata.irq_gpio_sel <<
				   CS35L36_INT_GPIO_SEL_SHIFT);

	/*
	 * Rev B0 has 2 versions
	 * L36 is 10V
	 * L37 is 12V
	 * If L36 we need to clamp some values for safety
	 * after probe has setup dt values. We want to make
	 * sure we dont miss any values set in probe
	 */
	if (cs35l36->chip_version == CS35L36_10V_L36) {
		regmap_update_bits(cs35l36->regmap,
				   CS35L36_BSTCVRT_OVERVOLT_CTRL,
				   CS35L36_BST_OVP_THLD_MASK,
				   CS35L36_BST_OVP_THLD_11V);

		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK1);
		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK2);

		regmap_update_bits(cs35l36->regmap, CS35L36_BST_ANA2_TEST,
				   CS35L36_BST_OVP_TRIM_MASK,
				   CS35L36_BST_OVP_TRIM_11V <<
				   CS35L36_BST_OVP_TRIM_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL2,
				   CS35L36_BST_CTRL_LIM_MASK,
				   1 << CS35L36_BST_CTRL_LIM_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL1,
				   CS35L35_BSTCVRT_CTL_MASK,
				   CS35L36_BST_CTRL_10V_CLAMP);
		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK1);
		regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK2);
	}

	/*
	 * RevA and B require the disabling of
	 * SYNC_GLOBAL_OVR when GLOBAL_EN = 0.
	 * Just turn it off from default
	 */
	regmap_update_bits(cs35l36->regmap, CS35L36_CTRL_OVRRIDE,
			   CS35L36_SYNC_GLOBAL_OVR_MASK,
			   0 << CS35L36_SYNC_GLOBAL_OVR_SHIFT);

	return 0;
}