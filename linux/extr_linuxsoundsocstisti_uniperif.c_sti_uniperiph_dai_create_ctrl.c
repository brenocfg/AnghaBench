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
struct uniperif {int num_ctrls; struct snd_kcontrol_new* snd_ctrls; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol_new {int /*<<< orphan*/  device; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int snd_soc_add_dai_controls (struct snd_soc_dai*,struct snd_kcontrol_new*,int) ; 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int sti_uniperiph_dai_create_ctrl(struct snd_soc_dai *dai)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *uni = priv->dai_data.uni;
	struct snd_kcontrol_new *ctrl;
	int i;

	if (!uni->num_ctrls)
		return 0;

	for (i = 0; i < uni->num_ctrls; i++) {
		/*
		 * Several Control can have same name. Controls are indexed on
		 * Uniperipheral instance ID
		 */
		ctrl = &uni->snd_ctrls[i];
		ctrl->index = uni->id;
		ctrl->device = uni->id;
	}

	return snd_soc_add_dai_controls(dai, uni->snd_ctrls, uni->num_ctrls);
}