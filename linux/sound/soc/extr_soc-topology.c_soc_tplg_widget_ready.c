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
struct soc_tplg {int /*<<< orphan*/  index; scalar_t__ comp; TYPE_1__* ops; } ;
struct snd_soc_tplg_dapm_widget {int dummy; } ;
struct snd_soc_dapm_widget {int dummy; } ;
struct TYPE_2__ {int (* widget_ready ) (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dapm_widget*,struct snd_soc_tplg_dapm_widget*) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dapm_widget*,struct snd_soc_tplg_dapm_widget*) ; 

__attribute__((used)) static int soc_tplg_widget_ready(struct soc_tplg *tplg,
	struct snd_soc_dapm_widget *w, struct snd_soc_tplg_dapm_widget *tplg_w)
{
	if (tplg->comp && tplg->ops && tplg->ops->widget_ready)
		return tplg->ops->widget_ready(tplg->comp, tplg->index, w,
			tplg_w);

	return 0;
}