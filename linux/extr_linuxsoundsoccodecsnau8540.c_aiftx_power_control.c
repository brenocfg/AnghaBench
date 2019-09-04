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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct nau8540 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8540_REG_RST ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nau8540* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aiftx_power_control(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		regmap_write(nau8540->regmap, NAU8540_REG_RST, 0x0001);
		regmap_write(nau8540->regmap, NAU8540_REG_RST, 0x0000);
	}
	return 0;
}