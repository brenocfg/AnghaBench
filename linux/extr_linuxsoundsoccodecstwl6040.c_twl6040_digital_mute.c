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
struct snd_soc_dai {int id; int /*<<< orphan*/  component; } ;

/* Variables and functions */
#define  TWL6040_DAI_DL1 130 
#define  TWL6040_DAI_DL2 129 
#define  TWL6040_DAI_LEGACY 128 
 int /*<<< orphan*/  twl6040_mute_path (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int twl6040_digital_mute(struct snd_soc_dai *dai, int mute)
{
	switch (dai->id) {
	case TWL6040_DAI_LEGACY:
		twl6040_mute_path(dai->component, TWL6040_DAI_DL1, mute);
		twl6040_mute_path(dai->component, TWL6040_DAI_DL2, mute);
		break;
	case TWL6040_DAI_DL1:
	case TWL6040_DAI_DL2:
		twl6040_mute_path(dai->component, dai->id, mute);
		break;
	default:
		break;
	}

	return 0;
}