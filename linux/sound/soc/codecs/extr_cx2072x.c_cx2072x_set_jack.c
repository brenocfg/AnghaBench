#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * gpiod_dev; struct snd_soc_component* data; } ;
struct cx2072x_priv {TYPE_1__ jack_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx2072x_disable_jack_detect (struct snd_soc_component*) ; 
 int /*<<< orphan*/  cx2072x_enable_jack_detect (struct snd_soc_component*) ; 
 TYPE_1__ cx2072x_jack_gpio ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_jack_add_gpios (struct snd_soc_jack*,int,TYPE_1__*) ; 

__attribute__((used)) static int cx2072x_set_jack(struct snd_soc_component *codec,
			    struct snd_soc_jack *jack, void *data)
{
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	int err;

	if (!jack) {
		cx2072x_disable_jack_detect(codec);
		return 0;
	}

	if (!cx2072x->jack_gpio.gpiod_dev) {
		cx2072x->jack_gpio = cx2072x_jack_gpio;
		cx2072x->jack_gpio.gpiod_dev = codec->dev;
		cx2072x->jack_gpio.data = codec;
		err = snd_soc_jack_add_gpios(jack, 1, &cx2072x->jack_gpio);
		if (err) {
			cx2072x->jack_gpio.gpiod_dev = NULL;
			return err;
		}
	}

	cx2072x_enable_jack_detect(codec);
	return 0;
}