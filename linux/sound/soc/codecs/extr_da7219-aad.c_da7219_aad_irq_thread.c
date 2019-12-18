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
typedef  int u8 ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct da7219_priv {int micbias_on_event; int /*<<< orphan*/  regmap; } ;
struct da7219_aad_priv {int jack_inserted; int /*<<< orphan*/  jack; int /*<<< orphan*/  hptest_work; int /*<<< orphan*/  btn_det_work; struct snd_soc_component* component; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t DA7219_AAD_IRQ_REG_A ; 
 size_t DA7219_AAD_IRQ_REG_B ; 
 int DA7219_AAD_IRQ_REG_MAX ; 
 int DA7219_AAD_MAX_BUTTONS ; 
 int DA7219_AAD_REPORT_ALL_MASK ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_1 ; 
 int /*<<< orphan*/  DA7219_ACCDET_IRQ_EVENT_A ; 
 int /*<<< orphan*/  DA7219_ACCDET_STATUS_A ; 
 int /*<<< orphan*/  DA7219_BUTTON_CONFIG_MASK ; 
 int DA7219_E_BUTTON_A_PRESSED_MASK ; 
 int DA7219_E_BUTTON_A_RELEASED_MASK ; 
 int DA7219_E_JACK_DETECT_COMPLETE_MASK ; 
 int DA7219_E_JACK_INSERTED_MASK ; 
 int DA7219_E_JACK_REMOVED_MASK ; 
 int /*<<< orphan*/  DA7219_HP_L_AMP_OE_MASK ; 
 int /*<<< orphan*/  DA7219_HP_L_CTRL ; 
 int /*<<< orphan*/  DA7219_HP_R_AMP_OE_MASK ; 
 int /*<<< orphan*/  DA7219_HP_R_CTRL ; 
 int DA7219_JACK_INSERTION_STS_MASK ; 
 int DA7219_JACK_TYPE_STS_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int SND_JACK_MECHANICAL ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t da7219_aad_irq_thread(int irq, void *data)
{
	struct da7219_aad_priv *da7219_aad = data;
	struct snd_soc_component *component = da7219_aad->component;
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	u8 events[DA7219_AAD_IRQ_REG_MAX];
	u8 statusa;
	int i, report = 0, mask = 0;

	/* Read current IRQ events */
	regmap_bulk_read(da7219->regmap, DA7219_ACCDET_IRQ_EVENT_A,
			 events, DA7219_AAD_IRQ_REG_MAX);

	if (!events[DA7219_AAD_IRQ_REG_A] && !events[DA7219_AAD_IRQ_REG_B])
		return IRQ_NONE;

	/* Read status register for jack insertion & type status */
	statusa = snd_soc_component_read32(component, DA7219_ACCDET_STATUS_A);

	/* Clear events */
	regmap_bulk_write(da7219->regmap, DA7219_ACCDET_IRQ_EVENT_A,
			  events, DA7219_AAD_IRQ_REG_MAX);

	dev_dbg(component->dev, "IRQ events = 0x%x|0x%x, status = 0x%x\n",
		events[DA7219_AAD_IRQ_REG_A], events[DA7219_AAD_IRQ_REG_B],
		statusa);

	if (statusa & DA7219_JACK_INSERTION_STS_MASK) {
		/* Jack Insertion */
		if (events[DA7219_AAD_IRQ_REG_A] &
		    DA7219_E_JACK_INSERTED_MASK) {
			report |= SND_JACK_MECHANICAL;
			mask |= SND_JACK_MECHANICAL;
			da7219_aad->jack_inserted = true;
		}

		/* Jack type detection */
		if (events[DA7219_AAD_IRQ_REG_A] &
		    DA7219_E_JACK_DETECT_COMPLETE_MASK) {
			/*
			 * If 4-pole, then enable button detection, else perform
			 * HP impedance test to determine output type to report.
			 *
			 * We schedule work here as the tasks themselves can
			 * take time to complete, and in particular for hptest
			 * we want to be able to check if the jack was removed
			 * during the procedure as this will invalidate the
			 * result. By doing this as work, the IRQ thread can
			 * handle a removal, and we can check at the end of
			 * hptest if we have a valid result or not.
			 */
			if (statusa & DA7219_JACK_TYPE_STS_MASK) {
				report |= SND_JACK_HEADSET;
				mask |=	SND_JACK_HEADSET | SND_JACK_LINEOUT;
				schedule_work(&da7219_aad->btn_det_work);
			} else {
				schedule_work(&da7219_aad->hptest_work);
			}
		}

		/* Button support for 4-pole jack */
		if (statusa & DA7219_JACK_TYPE_STS_MASK) {
			for (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) {
				/* Button Press */
				if (events[DA7219_AAD_IRQ_REG_B] &
				    (DA7219_E_BUTTON_A_PRESSED_MASK << i)) {
					report |= SND_JACK_BTN_0 >> i;
					mask |= SND_JACK_BTN_0 >> i;
				}
			}
			snd_soc_jack_report(da7219_aad->jack, report, mask);

			for (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) {
				/* Button Release */
				if (events[DA7219_AAD_IRQ_REG_B] &
				    (DA7219_E_BUTTON_A_RELEASED_MASK >> i)) {
					report &= ~(SND_JACK_BTN_0 >> i);
					mask |= SND_JACK_BTN_0 >> i;
				}
			}
		}
	} else {
		/* Jack removal */
		if (events[DA7219_AAD_IRQ_REG_A] & DA7219_E_JACK_REMOVED_MASK) {
			report = 0;
			mask |= DA7219_AAD_REPORT_ALL_MASK;
			da7219_aad->jack_inserted = false;

			/* Un-drive headphones/lineout */
			snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
					    DA7219_HP_R_AMP_OE_MASK, 0);
			snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
					    DA7219_HP_L_AMP_OE_MASK, 0);

			/* Ensure button detection disabled */
			snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
					    DA7219_BUTTON_CONFIG_MASK, 0);

			da7219->micbias_on_event = false;

			/* Disable mic bias */
			snd_soc_dapm_disable_pin(dapm, "Mic Bias");
			snd_soc_dapm_sync(dapm);

			/* Cancel any pending work */
			cancel_work_sync(&da7219_aad->btn_det_work);
			cancel_work_sync(&da7219_aad->hptest_work);
		}
	}

	snd_soc_jack_report(da7219_aad->jack, report, mask);

	return IRQ_HANDLED;
}