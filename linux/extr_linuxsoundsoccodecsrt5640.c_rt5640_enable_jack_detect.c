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
struct snd_soc_jack {int status; } ;
struct snd_soc_component {int dummy; } ;
struct rt5640_priv {int jd_src; int ovcd_sf; int ovcd_th; int /*<<< orphan*/  jack_work; int /*<<< orphan*/  irq; struct snd_soc_jack* jack; scalar_t__ jd_inverted; } ;

/* Variables and functions */
 scalar_t__ RT5640_BIAS_CUR4 ; 
 scalar_t__ RT5640_DUMMY1 ; 
 scalar_t__ RT5640_DUMMY2 ; 
 int RT5640_GP1_PF_MASK ; 
 int RT5640_GP1_PF_OUT ; 
 int RT5640_GP1_PIN_IRQ ; 
 int RT5640_GP1_PIN_MASK ; 
 int /*<<< orphan*/  RT5640_GPIO_CTRL1 ; 
 int /*<<< orphan*/  RT5640_GPIO_CTRL3 ; 
 scalar_t__ RT5640_IRQ_CTRL1 ; 
 int /*<<< orphan*/  RT5640_IRQ_CTRL2 ; 
 int RT5640_IRQ_JD_NOR ; 
 int /*<<< orphan*/  RT5640_JD_CTRL ; 
 int RT5640_JD_MASK ; 
 int RT5640_JD_P_INV ; 
 int RT5640_MB1_OC_STKY_EN ; 
 int RT5640_MB1_OC_STKY_MASK ; 
 int RT5640_MIC1_OVCD_EN ; 
 int RT5640_MIC1_OVCD_MASK ; 
 int RT5640_MIC1_OVTH_MASK ; 
 int /*<<< orphan*/  RT5640_MICBIAS ; 
 scalar_t__ RT5640_PR_BASE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5640_enable_micbias1_for_ovcd (struct snd_soc_component*) ; 
 int /*<<< orphan*/  rt5640_enable_micbias1_ovcd_irq (struct snd_soc_component*) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,int) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static void rt5640_enable_jack_detect(struct snd_soc_component *component,
				      struct snd_soc_jack *jack)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	/* Select JD-source */
	snd_soc_component_update_bits(component, RT5640_JD_CTRL,
		RT5640_JD_MASK, rt5640->jd_src);

	/* Selecting GPIO01 as an interrupt */
	snd_soc_component_update_bits(component, RT5640_GPIO_CTRL1,
		RT5640_GP1_PIN_MASK, RT5640_GP1_PIN_IRQ);

	/* Set GPIO1 output */
	snd_soc_component_update_bits(component, RT5640_GPIO_CTRL3,
		RT5640_GP1_PF_MASK, RT5640_GP1_PF_OUT);

	/* Enabling jd2 in general control 1 */
	snd_soc_component_write(component, RT5640_DUMMY1, 0x3f41);

	/* Enabling jd2 in general control 2 */
	snd_soc_component_write(component, RT5640_DUMMY2, 0x4001);

	snd_soc_component_write(component, RT5640_PR_BASE + RT5640_BIAS_CUR4,
		0xa800 | rt5640->ovcd_sf);

	snd_soc_component_update_bits(component, RT5640_MICBIAS,
		RT5640_MIC1_OVTH_MASK | RT5640_MIC1_OVCD_MASK,
		rt5640->ovcd_th | RT5640_MIC1_OVCD_EN);

	/*
	 * The over-current-detect is only reliable in detecting the absence
	 * of over-current, when the mic-contact in the jack is short-circuited,
	 * the hardware periodically retries if it can apply the bias-current
	 * leading to the ovcd status flip-flopping 1-0-1 with it being 0 about
	 * 10% of the time, as we poll the ovcd status bit we might hit that
	 * 10%, so we enable sticky mode and when checking OVCD we clear the
	 * status, msleep() a bit and then check to get a reliable reading.
	 */
	snd_soc_component_update_bits(component, RT5640_IRQ_CTRL2,
		RT5640_MB1_OC_STKY_MASK, RT5640_MB1_OC_STKY_EN);

	/*
	 * All IRQs get or-ed together, so we need the jack IRQ to report 0
	 * when a jack is inserted so that the OVCD IRQ then toggles the IRQ
	 * pin 0/1 instead of it being stuck to 1. So we invert the JD polarity
	 * on systems where the hardware does not already do this.
	 */
	if (rt5640->jd_inverted)
		snd_soc_component_write(component, RT5640_IRQ_CTRL1,
					RT5640_IRQ_JD_NOR);
	else
		snd_soc_component_write(component, RT5640_IRQ_CTRL1,
					RT5640_IRQ_JD_NOR | RT5640_JD_P_INV);

	rt5640->jack = jack;
	if (rt5640->jack->status & SND_JACK_MICROPHONE) {
		rt5640_enable_micbias1_for_ovcd(component);
		rt5640_enable_micbias1_ovcd_irq(component);
	}

	enable_irq(rt5640->irq);
	/* sync initial jack state */
	queue_work(system_long_wq, &rt5640->jack_work);
}