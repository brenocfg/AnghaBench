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
struct snd_soc_tplg_ctl_hdr {int dummy; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_2__ {int (* control_load ) (scalar_t__,int /*<<< orphan*/ ,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__,int /*<<< orphan*/ ,struct snd_kcontrol_new*,struct snd_soc_tplg_ctl_hdr*) ; 

__attribute__((used)) static int soc_tplg_init_kcontrol(struct soc_tplg *tplg,
	struct snd_kcontrol_new *k, struct snd_soc_tplg_ctl_hdr *hdr)
{
	if (tplg->comp && tplg->ops && tplg->ops->control_load)
		return tplg->ops->control_load(tplg->comp, tplg->index, k,
			hdr);

	return 0;
}