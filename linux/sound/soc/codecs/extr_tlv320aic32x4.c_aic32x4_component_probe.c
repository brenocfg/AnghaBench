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
typedef  int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct clk_bulk_data {char* id; int /*<<< orphan*/  clk; } ;
struct aic32x4_priv {int power_cfg; int micpga_routing; scalar_t__ setup; int /*<<< orphan*/  rstn_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_ADCSETUP ; 
 int AIC32X4_AVDDWEAKDISABLE ; 
 int /*<<< orphan*/  AIC32X4_CMMODE ; 
 int AIC32X4_LADC_EN ; 
 int /*<<< orphan*/  AIC32X4_LDOCTL ; 
 int AIC32X4_LDOCTLEN ; 
 int AIC32X4_LDOIN2HP ; 
 int AIC32X4_LDOIN_18_36 ; 
 int /*<<< orphan*/  AIC32X4_LMICPGANIN ; 
 int AIC32X4_LMICPGANIN_CM1L_10K ; 
 int AIC32X4_LMICPGANIN_IN2R_10K ; 
 int /*<<< orphan*/  AIC32X4_MICBIAS ; 
 int AIC32X4_MICBIAS_2075V ; 
 int AIC32X4_MICBIAS_LDOIN ; 
 int AIC32X4_MICPGA_ROUTE_LMIC_IN2R_10K ; 
 int AIC32X4_MICPGA_ROUTE_RMIC_IN1L_10K ; 
 int /*<<< orphan*/  AIC32X4_PWRCFG ; 
 int AIC32X4_PWR_AIC32X4_LDO_ENABLE ; 
 int AIC32X4_PWR_AVDD_DVDD_WEAK_DISABLE ; 
 int AIC32X4_PWR_CMMODE_HP_LDOIN_POWERED ; 
 int AIC32X4_PWR_CMMODE_LDOIN_RANGE_18_36 ; 
 int AIC32X4_PWR_MICBIAS_2075_LDOIN ; 
 int AIC32X4_RADC_EN ; 
 int /*<<< orphan*/  AIC32X4_RESET ; 
 int /*<<< orphan*/  AIC32X4_RMICPGANIN ; 
 int AIC32X4_RMICPGANIN_CM1R_10K ; 
 int AIC32X4_RMICPGANIN_IN1L_10K ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct clk_bulk_data*) ; 
 int /*<<< orphan*/  aic32x4_setup_gpios (struct snd_soc_component*) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_clk_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_bulk_data*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 struct aic32x4_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic32x4_component_probe(struct snd_soc_component *component)
{
	struct aic32x4_priv *aic32x4 = snd_soc_component_get_drvdata(component);
	u32 tmp_reg;
	int ret;

	struct clk_bulk_data clocks[] = {
		{ .id = "codec_clkin" },
		{ .id = "pll" },
		{ .id = "bdiv" },
		{ .id = "mdac" },
	};

	ret = devm_clk_bulk_get(component->dev, ARRAY_SIZE(clocks), clocks);
	if (ret)
		return ret;

	if (gpio_is_valid(aic32x4->rstn_gpio)) {
		ndelay(10);
		gpio_set_value(aic32x4->rstn_gpio, 1);
		mdelay(1);
	}

	snd_soc_component_write(component, AIC32X4_RESET, 0x01);

	if (aic32x4->setup)
		aic32x4_setup_gpios(component);

	clk_set_parent(clocks[0].clk, clocks[1].clk);
	clk_set_parent(clocks[2].clk, clocks[3].clk);

	/* Power platform configuration */
	if (aic32x4->power_cfg & AIC32X4_PWR_MICBIAS_2075_LDOIN) {
		snd_soc_component_write(component, AIC32X4_MICBIAS,
				AIC32X4_MICBIAS_LDOIN | AIC32X4_MICBIAS_2075V);
	}
	if (aic32x4->power_cfg & AIC32X4_PWR_AVDD_DVDD_WEAK_DISABLE)
		snd_soc_component_write(component, AIC32X4_PWRCFG, AIC32X4_AVDDWEAKDISABLE);

	tmp_reg = (aic32x4->power_cfg & AIC32X4_PWR_AIC32X4_LDO_ENABLE) ?
			AIC32X4_LDOCTLEN : 0;
	snd_soc_component_write(component, AIC32X4_LDOCTL, tmp_reg);

	tmp_reg = snd_soc_component_read32(component, AIC32X4_CMMODE);
	if (aic32x4->power_cfg & AIC32X4_PWR_CMMODE_LDOIN_RANGE_18_36)
		tmp_reg |= AIC32X4_LDOIN_18_36;
	if (aic32x4->power_cfg & AIC32X4_PWR_CMMODE_HP_LDOIN_POWERED)
		tmp_reg |= AIC32X4_LDOIN2HP;
	snd_soc_component_write(component, AIC32X4_CMMODE, tmp_reg);

	/* Mic PGA routing */
	if (aic32x4->micpga_routing & AIC32X4_MICPGA_ROUTE_LMIC_IN2R_10K)
		snd_soc_component_write(component, AIC32X4_LMICPGANIN,
				AIC32X4_LMICPGANIN_IN2R_10K);
	else
		snd_soc_component_write(component, AIC32X4_LMICPGANIN,
				AIC32X4_LMICPGANIN_CM1L_10K);
	if (aic32x4->micpga_routing & AIC32X4_MICPGA_ROUTE_RMIC_IN1L_10K)
		snd_soc_component_write(component, AIC32X4_RMICPGANIN,
				AIC32X4_RMICPGANIN_IN1L_10K);
	else
		snd_soc_component_write(component, AIC32X4_RMICPGANIN,
				AIC32X4_RMICPGANIN_CM1R_10K);

	/*
	 * Workaround: for an unknown reason, the ADC needs to be powered up
	 * and down for the first capture to work properly. It seems related to
	 * a HW BUG or some kind of behavior not documented in the datasheet.
	 */
	tmp_reg = snd_soc_component_read32(component, AIC32X4_ADCSETUP);
	snd_soc_component_write(component, AIC32X4_ADCSETUP, tmp_reg |
				AIC32X4_LADC_EN | AIC32X4_RADC_EN);
	snd_soc_component_write(component, AIC32X4_ADCSETUP, tmp_reg);

	return 0;
}