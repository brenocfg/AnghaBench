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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct es8328_priv {scalar_t__ playback_fs; scalar_t__ deemph; } ;
struct TYPE_3__ {int val; scalar_t__ rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ES8328_DACCONTROL6 ; 
 int /*<<< orphan*/  ES8328_DACCONTROL6_DEEMPH_MASK ; 
 int ES8328_DACCONTROL6_DEEMPH_OFF ; 
 scalar_t__ abs (scalar_t__) ; 
 TYPE_1__* deemph_settings ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int es8328_set_deemph(struct snd_soc_component *component)
{
	struct es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	int val, i, best;

	/*
	 * If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	if (es8328->deemph) {
		best = 0;
		for (i = 1; i < ARRAY_SIZE(deemph_settings); i++) {
			if (abs(deemph_settings[i].rate - es8328->playback_fs) <
			    abs(deemph_settings[best].rate - es8328->playback_fs))
				best = i;
		}

		val = deemph_settings[best].val;
	} else {
		val = ES8328_DACCONTROL6_DEEMPH_OFF;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	return snd_soc_component_update_bits(component, ES8328_DACCONTROL6,
			ES8328_DACCONTROL6_DEEMPH_MASK, val);
}