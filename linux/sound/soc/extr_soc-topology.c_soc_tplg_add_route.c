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
struct snd_soc_dapm_route {int dummy; } ;
struct TYPE_2__ {int (* dapm_route_load ) (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dapm_route*) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dapm_route*) ; 

__attribute__((used)) static int soc_tplg_add_route(struct soc_tplg *tplg,
	struct snd_soc_dapm_route *route)
{
	if (tplg->comp && tplg->ops && tplg->ops->dapm_route_load)
		return tplg->ops->dapm_route_load(tplg->comp, tplg->index,
			route);

	return 0;
}