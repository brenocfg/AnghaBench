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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs42xx8_priv {int tx_channels; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42XX8_DACMUTE ; 
 int CS42XX8_DACMUTE_ALL ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42xx8_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	u8 dac_unmute = cs42xx8->tx_channels ?
		        ~((0x1 << cs42xx8->tx_channels) - 1) : 0;

	regmap_write(cs42xx8->regmap, CS42XX8_DACMUTE,
		     mute ? CS42XX8_DACMUTE_ALL : dac_unmute);

	return 0;
}