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
struct ak4641_priv {scalar_t__ playback_fs; scalar_t__ deemph; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4641_DAC ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__* deemph_settings ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct ak4641_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak4641_set_deemph(struct snd_soc_component *component)
{
	struct ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	int i, best = 0;

	for (i = 0 ; i < ARRAY_SIZE(deemph_settings); i++) {
		/* if deemphasis is on, select the nearest available rate */
		if (ak4641->deemph && deemph_settings[i] != 0 &&
		    abs(deemph_settings[i] - ak4641->playback_fs) <
		    abs(deemph_settings[best] - ak4641->playback_fs))
			best = i;

		if (!ak4641->deemph && deemph_settings[i] == 0)
			best = i;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", best);

	return snd_soc_component_update_bits(component, AK4641_DAC, 0x3, best);
}