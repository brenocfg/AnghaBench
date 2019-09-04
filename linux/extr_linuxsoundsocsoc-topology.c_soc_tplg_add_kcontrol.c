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
struct soc_tplg {struct snd_soc_component* comp; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int soc_tplg_add_dcontrol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_kcontrol_new*,int /*<<< orphan*/ *,struct snd_soc_component*,struct snd_kcontrol**) ; 

__attribute__((used)) static int soc_tplg_add_kcontrol(struct soc_tplg *tplg,
	struct snd_kcontrol_new *k, struct snd_kcontrol **kcontrol)
{
	struct snd_soc_component *comp = tplg->comp;

	return soc_tplg_add_dcontrol(comp->card->snd_card,
				comp->dev, k, NULL, comp, kcontrol);
}