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
struct rt5651_priv {int jd_src; scalar_t__ jd_active_high; scalar_t__ gpiod_hp_det; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5651_INT_IRQ_ST ; 
#define  RT5651_JD1_1 130 
#define  RT5651_JD1_2 129 
#define  RT5651_JD2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int gpiod_get_value_cansleep (scalar_t__) ; 
 struct rt5651_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt5651_jack_inserted(struct snd_soc_component *component)
{
	struct rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	int val;

	if (rt5651->gpiod_hp_det) {
		val = gpiod_get_value_cansleep(rt5651->gpiod_hp_det);
		dev_dbg(component->dev, "jack-detect gpio %d\n", val);
		return val;
	}

	val = snd_soc_component_read32(component, RT5651_INT_IRQ_ST);
	dev_dbg(component->dev, "irq status %#04x\n", val);

	switch (rt5651->jd_src) {
	case RT5651_JD1_1:
		val &= 0x1000;
		break;
	case RT5651_JD1_2:
		val &= 0x2000;
		break;
	case RT5651_JD2:
		val &= 0x4000;
		break;
	default:
		break;
	}

	if (rt5651->jd_active_high)
		return val != 0;
	else
		return val == 0;
}