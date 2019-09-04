#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
struct snd_soc_dapm_widget {TYPE_2__ dobj; TYPE_1__* dapm; } ;
struct TYPE_3__ {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DOBJ_WIDGET ; 
 int /*<<< orphan*/  SOC_TPLG_PASS_WIDGET ; 
 int /*<<< orphan*/  remove_widget (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void snd_soc_tplg_widget_remove(struct snd_soc_dapm_widget *w)
{
	/* make sure we are a widget */
	if (w->dobj.type != SND_SOC_DOBJ_WIDGET)
		return;

	remove_widget(w->dapm->component, &w->dobj, SOC_TPLG_PASS_WIDGET);
}