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
struct alc5632_priv {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  alc5632_vol_snd_controls ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alc5632_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int alc5632_probe(struct snd_soc_component *component)
{
	struct alc5632_priv *alc5632 = snd_soc_component_get_drvdata(component);

	switch (alc5632->id) {
	case 0x5c:
		snd_soc_add_component_controls(component, alc5632_vol_snd_controls,
			ARRAY_SIZE(alc5632_vol_snd_controls));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}