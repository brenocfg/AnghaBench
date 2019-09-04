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
struct cs4270_private {int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4270_MUTE ; 
 int CS4270_MUTE_AUTO ; 
 int /*<<< orphan*/  CS4270_TRANS ; 
 int CS4270_TRANS_SOFT ; 
 int CS4270_TRANS_ZERO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs4270_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4270_probe(struct snd_soc_component *component)
{
	struct cs4270_private *cs4270 = snd_soc_component_get_drvdata(component);
	int ret;

	/* Disable auto-mute.  This feature appears to be buggy.  In some
	 * situations, auto-mute will not deactivate when it should, so we want
	 * this feature disabled by default.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */
	ret = snd_soc_component_update_bits(component, CS4270_MUTE, CS4270_MUTE_AUTO, 0);
	if (ret < 0) {
		dev_err(component->dev, "i2c write failed\n");
		return ret;
	}

	/* Disable automatic volume control.  The hardware enables, and it
	 * causes volume change commands to be delayed, sometimes until after
	 * playback has started.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */
	ret = snd_soc_component_update_bits(component, CS4270_TRANS,
		CS4270_TRANS_SOFT | CS4270_TRANS_ZERO, 0);
	if (ret < 0) {
		dev_err(component->dev, "i2c write failed\n");
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4270->supplies),
				    cs4270->supplies);

	return ret;
}