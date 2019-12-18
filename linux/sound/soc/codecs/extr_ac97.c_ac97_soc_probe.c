#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {TYPE_1__* card; } ;
struct snd_ac97_template {int dummy; } ;
struct snd_ac97_bus {int dummy; } ;
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct snd_ac97_template*,int /*<<< orphan*/ ,int) ; 
 int snd_ac97_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_ac97_bus**) ; 
 int snd_ac97_mixer (struct snd_ac97_bus*,struct snd_ac97_template*,struct snd_ac97**) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct snd_ac97*) ; 
 int /*<<< orphan*/  soc_ac97_ops ; 

__attribute__((used)) static int ac97_soc_probe(struct snd_soc_component *component)
{
	struct snd_ac97 *ac97;
	struct snd_ac97_bus *ac97_bus;
	struct snd_ac97_template ac97_template;
	int ret;

	/* add codec as bus device for standard ac97 */
	ret = snd_ac97_bus(component->card->snd_card, 0, soc_ac97_ops,
			   NULL, &ac97_bus);
	if (ret < 0)
		return ret;

	memset(&ac97_template, 0, sizeof(struct snd_ac97_template));
	ret = snd_ac97_mixer(ac97_bus, &ac97_template, &ac97);
	if (ret < 0)
		return ret;

	snd_soc_component_set_drvdata(component, ac97);

	return 0;
}