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
struct wm8996_priv {int detecting; int /*<<< orphan*/  jack; scalar_t__ jack_mic; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  WM8996_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  WM8996_ANALOGUE_HP_1 ; 
 int /*<<< orphan*/  WM8996_HEADPHONE_DETECT_2 ; 
 int WM8996_HPOUT1L_ENA ; 
 int WM8996_HPOUT1L_RMV_SHORT ; 
 int WM8996_HPOUT1R_RMV_SHORT ; 
 int WM8996_HP_DONE ; 
 int WM8996_HP_LVL_MASK ; 
 int WM8996_JD_MODE_MASK ; 
 int WM8996_MICD_ENA ; 
 int /*<<< orphan*/  WM8996_MIC_DETECT_1 ; 
 int /*<<< orphan*/  WM8996_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm8996_hpdet_irq(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	int val, reg, report;

	/* Assume headphone in error conditions; we need to report
	 * something or we stall our state machine.
	 */
	report = SND_JACK_HEADPHONE;

	reg = snd_soc_component_read32(component, WM8996_HEADPHONE_DETECT_2);
	if (reg < 0) {
		dev_err(component->dev, "Failed to read HPDET status\n");
		goto out;
	}

	if (!(reg & WM8996_HP_DONE)) {
		dev_err(component->dev, "Got HPDET IRQ but HPDET is busy\n");
		goto out;
	}

	val = reg & WM8996_HP_LVL_MASK;

	dev_dbg(component->dev, "HPDET measured %d ohms\n", val);

	/* If we've got high enough impedence then report as line,
	 * otherwise assume headphone.
	 */
	if (val >= 126)
		report = SND_JACK_LINEOUT;
	else
		report = SND_JACK_HEADPHONE;

out:
	if (wm8996->jack_mic)
		report |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(wm8996->jack, report,
			    SND_JACK_LINEOUT | SND_JACK_HEADSET);

	wm8996->detecting = false;

	/* If the output isn't running re-clamp it */
	if (!(snd_soc_component_read32(component, WM8996_POWER_MANAGEMENT_1) &
	      (WM8996_HPOUT1L_ENA | WM8996_HPOUT1R_RMV_SHORT)))
		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1,
				    WM8996_HPOUT1L_RMV_SHORT |
				    WM8996_HPOUT1R_RMV_SHORT, 0);

	/* Go back to looking at the microphone */
	snd_soc_component_update_bits(component, WM8996_ACCESSORY_DETECT_MODE_1,
			    WM8996_JD_MODE_MASK, 0);
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1, WM8996_MICD_ENA,
			    WM8996_MICD_ENA);

	snd_soc_dapm_disable_pin(dapm, "Bandgap");
	snd_soc_dapm_sync(dapm);
}