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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct cx2072x_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_ANALOG_TEST12 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST1 ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST15 ; 
 int /*<<< orphan*/  CX2072X_GPIO_STICKY_MASK ; 
 int /*<<< orphan*/  CX2072X_PORTA_UNSOLICITED_RESPONSE ; 
 int /*<<< orphan*/  CX2072X_UM_INTERRUPT_CRTL_E ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void cx2072x_enable_jack_detect(struct snd_soc_component *codec)
{
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	/* No-sticky input type */
	regmap_write(cx2072x->regmap, CX2072X_GPIO_STICKY_MASK, 0x1f);

	/* Use GPOI0 as interrupt pin */
	regmap_write(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0x12 << 24);

	/* Enables unsolitited message on PortA */
	regmap_write(cx2072x->regmap, CX2072X_PORTA_UNSOLICITED_RESPONSE, 0x80);

	/* support both nokia and apple headset set. Monitor time = 275 ms */
	regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST15, 0x73);

	/* Disable TIP detection */
	regmap_write(cx2072x->regmap, CX2072X_ANALOG_TEST12, 0x300);

	/* Switch MusicD3Live pin to GPIO */
	regmap_write(cx2072x->regmap, CX2072X_DIGITAL_TEST1, 0);

	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_force_enable_pin_unlocked(dapm, "PORTD");
	snd_soc_dapm_force_enable_pin_unlocked(dapm, "Headset Bias");
	snd_soc_dapm_force_enable_pin_unlocked(dapm, "PortD Mic Bias");

	snd_soc_dapm_mutex_unlock(dapm);
}