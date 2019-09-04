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
struct wm5100_priv {int jack_mic; int jack_detecting; int jack_flips; int /*<<< orphan*/  jack; int /*<<< orphan*/  dev; int /*<<< orphan*/  jack_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int WM5100_ACCDET_RATE_MASK ; 
 int WM5100_ACCDET_RATE_SHIFT ; 
 unsigned int WM5100_ACCDET_STS ; 
 unsigned int WM5100_ACCDET_VALID ; 
 int /*<<< orphan*/  WM5100_MIC_DETECT_1 ; 
 int /*<<< orphan*/  WM5100_MIC_DETECT_3 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm5100_report_headphone (struct wm5100_priv*) ; 
 int /*<<< orphan*/  wm5100_set_detect_mode (struct wm5100_priv*,int) ; 

__attribute__((used)) static void wm5100_micd_irq(struct wm5100_priv *wm5100)
{
	unsigned int val;
	int ret;

	ret = regmap_read(wm5100->regmap, WM5100_MIC_DETECT_3, &val);
	if (ret != 0) {
		dev_err(wm5100->dev, "Failed to read microphone status: %d\n",
			ret);
		return;
	}

	dev_dbg(wm5100->dev, "Microphone event: %x\n", val);

	if (!(val & WM5100_ACCDET_VALID)) {
		dev_warn(wm5100->dev, "Microphone detection state invalid\n");
		return;
	}

	/* No accessory, reset everything and report removal */
	if (!(val & WM5100_ACCDET_STS)) {
		dev_dbg(wm5100->dev, "Jack removal detected\n");
		wm5100->jack_mic = false;
		wm5100->jack_detecting = true;
		wm5100->jack_flips = 0;
		snd_soc_jack_report(wm5100->jack, 0,
				    SND_JACK_LINEOUT | SND_JACK_HEADSET |
				    SND_JACK_BTN_0);

		regmap_update_bits(wm5100->regmap, WM5100_MIC_DETECT_1,
				   WM5100_ACCDET_RATE_MASK,
				   WM5100_ACCDET_RATE_MASK);
		return;
	}

	/* If the measurement is very high we've got a microphone,
	 * either we just detected one or if we already reported then
	 * we've got a button release event.
	 */
	if (val & 0x400) {
		if (wm5100->jack_detecting) {
			dev_dbg(wm5100->dev, "Microphone detected\n");
			wm5100->jack_mic = true;
			wm5100->jack_detecting = false;
			snd_soc_jack_report(wm5100->jack,
					    SND_JACK_HEADSET,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);

			/* Increase poll rate to give better responsiveness
			 * for buttons */
			regmap_update_bits(wm5100->regmap, WM5100_MIC_DETECT_1,
					   WM5100_ACCDET_RATE_MASK,
					   5 << WM5100_ACCDET_RATE_SHIFT);
		} else {
			dev_dbg(wm5100->dev, "Mic button up\n");
			snd_soc_jack_report(wm5100->jack, 0, SND_JACK_BTN_0);
		}

		return;
	}

	/* If we detected a lower impedence during initial startup
	 * then we probably have the wrong polarity, flip it.  Don't
	 * do this for the lowest impedences to speed up detection of
	 * plain headphones and give up if neither polarity looks
	 * sensible.
	 */
	if (wm5100->jack_detecting && (val & 0x3f8)) {
		wm5100->jack_flips++;

		if (wm5100->jack_flips > 1)
			wm5100_report_headphone(wm5100);
		else
			wm5100_set_detect_mode(wm5100, !wm5100->jack_mode);

		return;
	}

	/* Don't distinguish between buttons, just report any low
	 * impedence as BTN_0.
	 */
	if (val & 0x3fc) {
		if (wm5100->jack_mic) {
			dev_dbg(wm5100->dev, "Mic button detected\n");
			snd_soc_jack_report(wm5100->jack, SND_JACK_BTN_0,
					    SND_JACK_BTN_0);
		} else if (wm5100->jack_detecting) {
			wm5100_report_headphone(wm5100);
		}
	}
}