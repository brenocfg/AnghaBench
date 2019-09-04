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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98095_priv {unsigned int sysclk; scalar_t__ mic2pre; scalar_t__ mic1pre; scalar_t__ lin_state; struct max98095_cdata* dai; scalar_t__ bq_textcnt; scalar_t__ eq_textcnt; int /*<<< orphan*/  mclk; } ;
struct max98095_cdata {unsigned int rate; unsigned int fmt; scalar_t__ bq_sel; scalar_t__ eq_sel; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  M98095_02C_DAI1_IOCFG ; 
 int /*<<< orphan*/  M98095_036_DAI2_IOCFG ; 
 int /*<<< orphan*/  M98095_040_DAI3_IOCFG ; 
 int /*<<< orphan*/  M98095_045_CFG_DSP ; 
 int /*<<< orphan*/  M98095_048_MIX_DAC_LR ; 
 int /*<<< orphan*/  M98095_049_MIX_DAC_M ; 
 int /*<<< orphan*/  M98095_04E_CFG_HP ; 
 int /*<<< orphan*/  M98095_092_PWR_EN_OUT ; 
 int /*<<< orphan*/  M98095_097_PWR_SYS ; 
 int /*<<< orphan*/  M98095_0FF_REV_ID ; 
 int M98095_DAI1L_TO_DACL ; 
 int M98095_DAI1R_TO_DACR ; 
 int M98095_DAI2M_TO_DACM ; 
 int M98095_DAI3M_TO_DACM ; 
 int M98095_DSPNORMAL ; 
 int M98095_HPNORMAL ; 
 int M98095_PWRSV ; 
 int M98095_S1NORMAL ; 
 int M98095_S2NORMAL ; 
 int M98095_S3NORMAL ; 
 int M98095_SDATA ; 
 int /*<<< orphan*/  M98095_SHDNRUN ; 
 int M98095_SPK_SPREADSPECTRUM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98095_handle_pdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98095_report_jack ; 
 int /*<<< orphan*/  max98095_reset (struct snd_soc_component*) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct snd_soc_component*) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98095_probe(struct snd_soc_component *component)
{
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct max98095_cdata *cdata;
	struct i2c_client *client;
	int ret = 0;

	max98095->mclk = devm_clk_get(component->dev, "mclk");
	if (PTR_ERR(max98095->mclk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	/* reset the codec, the DSP core, and disable all interrupts */
	max98095_reset(component);

	client = to_i2c_client(component->dev);

	/* initialize private data */

	max98095->sysclk = (unsigned)-1;
	max98095->eq_textcnt = 0;
	max98095->bq_textcnt = 0;

	cdata = &max98095->dai[0];
	cdata->rate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	cdata = &max98095->dai[1];
	cdata->rate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	cdata = &max98095->dai[2];
	cdata->rate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sel = 0;
	cdata->bq_sel = 0;

	max98095->lin_state = 0;
	max98095->mic1pre = 0;
	max98095->mic2pre = 0;

	if (client->irq) {
		/* register an audio interrupt */
		ret = request_threaded_irq(client->irq, NULL,
			max98095_report_jack,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT, "max98095", component);
		if (ret) {
			dev_err(component->dev, "Failed to request IRQ: %d\n", ret);
			goto err_access;
		}
	}

	ret = snd_soc_component_read32(component, M98095_0FF_REV_ID);
	if (ret < 0) {
		dev_err(component->dev, "Failure reading hardware revision: %d\n",
			ret);
		goto err_irq;
	}
	dev_info(component->dev, "Hardware revision: %c\n", ret - 0x40 + 'A');

	snd_soc_component_write(component, M98095_097_PWR_SYS, M98095_PWRSV);

	snd_soc_component_write(component, M98095_048_MIX_DAC_LR,
		M98095_DAI1L_TO_DACL|M98095_DAI1R_TO_DACR);

	snd_soc_component_write(component, M98095_049_MIX_DAC_M,
		M98095_DAI2M_TO_DACM|M98095_DAI3M_TO_DACM);

	snd_soc_component_write(component, M98095_092_PWR_EN_OUT, M98095_SPK_SPREADSPECTRUM);
	snd_soc_component_write(component, M98095_045_CFG_DSP, M98095_DSPNORMAL);
	snd_soc_component_write(component, M98095_04E_CFG_HP, M98095_HPNORMAL);

	snd_soc_component_write(component, M98095_02C_DAI1_IOCFG,
		M98095_S1NORMAL|M98095_SDATA);

	snd_soc_component_write(component, M98095_036_DAI2_IOCFG,
		M98095_S2NORMAL|M98095_SDATA);

	snd_soc_component_write(component, M98095_040_DAI3_IOCFG,
		M98095_S3NORMAL|M98095_SDATA);

	max98095_handle_pdata(component);

	/* take the codec out of the shut down */
	snd_soc_component_update_bits(component, M98095_097_PWR_SYS, M98095_SHDNRUN,
		M98095_SHDNRUN);

	return 0;

err_irq:
	if (client->irq)
		free_irq(client->irq, component);
err_access:
	return ret;
}