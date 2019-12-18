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
struct twl4030_priv {int codec_powered; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_AUDIO_RES_POWER ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int twl4030_audio_disable_resource (int /*<<< orphan*/ ) ; 
 int twl4030_audio_enable_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void twl4030_codec_enable(struct snd_soc_component *component, int enable)
{
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	int mode;

	if (enable == twl4030->codec_powered)
		return;

	if (enable)
		mode = twl4030_audio_enable_resource(TWL4030_AUDIO_RES_POWER);
	else
		mode = twl4030_audio_disable_resource(TWL4030_AUDIO_RES_POWER);

	if (mode >= 0)
		twl4030->codec_powered = enable;

	/* REVISIT: this delay is present in TI sample drivers */
	/* but there seems to be no TRM requirement for it     */
	udelay(10);
}