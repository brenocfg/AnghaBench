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
struct cx2072x_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_DIGITAL_TEST11 ; 
 int /*<<< orphan*/  CX2072X_PORTA_PIN_SENSE ; 
 int /*<<< orphan*/  CX2072X_UM_INTERRUPT_CRTL_E ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cx2072x_jack_status_check(void *data)
{
	struct snd_soc_component *codec = data;
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	unsigned int jack;
	unsigned int type = 0;
	int state = 0;

	mutex_lock(&cx2072x->lock);

	regmap_read(cx2072x->regmap, CX2072X_PORTA_PIN_SENSE, &jack);
	jack = jack >> 24;
	regmap_read(cx2072x->regmap, CX2072X_DIGITAL_TEST11, &type);

	if (jack == 0x80) {
		type = type >> 8;

		if (type & 0x8) {
			/* Apple headset */
			state |= SND_JACK_HEADSET;
			if (type & 0x2)
				state |= SND_JACK_BTN_0;
		} else if (type & 0x4) {
			/* Nokia headset */
			state |= SND_JACK_HEADPHONE;
		} else {
			/* Headphone */
			state |= SND_JACK_HEADPHONE;
		}
	}

	/* clear interrupt */
	regmap_write(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0x12 << 24);

	mutex_unlock(&cx2072x->lock);

	dev_dbg(codec->dev, "CX2072X_HSDETECT type=0x%X,Jack state = %x\n",
		type, state);
	return state;
}