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
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct nau8810 {struct regmap* regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int NAU8810_ABIAS_EN ; 
 int NAU8810_IOBUF_EN ; 
 int NAU8810_REFIMP_300K ; 
 int NAU8810_REFIMP_3K ; 
 int NAU8810_REFIMP_80K ; 
 int NAU8810_REFIMP_MASK ; 
 int /*<<< orphan*/  NAU8810_REG_POWER1 ; 
 int /*<<< orphan*/  NAU8810_REG_POWER2 ; 
 int /*<<< orphan*/  NAU8810_REG_POWER3 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_sync (struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct nau8810* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8810_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	struct regmap *map = nau8810->regmap;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_REFIMP_MASK, NAU8810_REFIMP_80K);
		break;

	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN);

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_sync(map);
			regmap_update_bits(map, NAU8810_REG_POWER1,
				NAU8810_REFIMP_MASK, NAU8810_REFIMP_3K);
			mdelay(100);
		}
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_REFIMP_MASK, NAU8810_REFIMP_300K);
		break;

	case SND_SOC_BIAS_OFF:
		regmap_write(map, NAU8810_REG_POWER1, 0);
		regmap_write(map, NAU8810_REG_POWER2, 0);
		regmap_write(map, NAU8810_REG_POWER3, 0);
		break;
	}

	return 0;
}