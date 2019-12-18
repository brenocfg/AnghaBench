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
struct twl6040_data {int dl1_unmuted; int dl2_unmuted; } ;
struct twl6040 {int dummy; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum twl6040_dai_id { ____Placeholder_twl6040_dai_id } twl6040_dai_id ;

/* Variables and functions */
#define  TWL6040_DAI_DL1 129 
#define  TWL6040_DAI_DL2 128 
 int TWL6040_HFDACENA ; 
 int TWL6040_HFDRVENA ; 
 int TWL6040_HFPGAENA ; 
 int TWL6040_HFSWENA ; 
 int TWL6040_HSDACENA ; 
 int TWL6040_HSDRVENA ; 
 int /*<<< orphan*/  TWL6040_REG_EARCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HFLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HFRCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HSLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HSRCTL ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 int twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void twl6040_mute_path(struct snd_soc_component *component, enum twl6040_dai_id id,
			     int mute)
{
	struct twl6040 *twl6040 = to_twl6040(component);
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	int hslctl, hsrctl, earctl;
	int hflctl, hfrctl;

	switch (id) {
	case TWL6040_DAI_DL1:
		hslctl = twl6040_read(component, TWL6040_REG_HSLCTL);
		hsrctl = twl6040_read(component, TWL6040_REG_HSRCTL);
		earctl = twl6040_read(component, TWL6040_REG_EARCTL);

		if (mute) {
			/* Power down drivers and DACs */
			earctl &= ~0x01;
			hslctl &= ~(TWL6040_HSDRVENA | TWL6040_HSDACENA);
			hsrctl &= ~(TWL6040_HSDRVENA | TWL6040_HSDACENA);

		}

		twl6040_reg_write(twl6040, TWL6040_REG_EARCTL, earctl);
		twl6040_reg_write(twl6040, TWL6040_REG_HSLCTL, hslctl);
		twl6040_reg_write(twl6040, TWL6040_REG_HSRCTL, hsrctl);
		priv->dl1_unmuted = !mute;
		break;
	case TWL6040_DAI_DL2:
		hflctl = twl6040_read(component, TWL6040_REG_HFLCTL);
		hfrctl = twl6040_read(component, TWL6040_REG_HFRCTL);

		if (mute) {
			/* Power down drivers and DACs */
			hflctl &= ~(TWL6040_HFDACENA | TWL6040_HFPGAENA |
				    TWL6040_HFDRVENA | TWL6040_HFSWENA);
			hfrctl &= ~(TWL6040_HFDACENA | TWL6040_HFPGAENA |
				    TWL6040_HFDRVENA | TWL6040_HFSWENA);
		}

		twl6040_reg_write(twl6040, TWL6040_REG_HFLCTL, hflctl);
		twl6040_reg_write(twl6040, TWL6040_REG_HFRCTL, hfrctl);
		priv->dl2_unmuted = !mute;
		break;
	default:
		break;
	}
}