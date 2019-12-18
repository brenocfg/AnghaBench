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
struct snd_soc_dobj {int /*<<< orphan*/  list; int /*<<< orphan*/  type; TYPE_1__* ops; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_unload ) (struct snd_soc_component*,struct snd_soc_dobj*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DOBJ_NONE ; 
 int SOC_TPLG_PASS_LINK ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_component*,struct snd_soc_dobj*) ; 

__attribute__((used)) static void remove_backend_link(struct snd_soc_component *comp,
	struct snd_soc_dobj *dobj, int pass)
{
	if (pass != SOC_TPLG_PASS_LINK)
		return;

	if (dobj->ops && dobj->ops->link_unload)
		dobj->ops->link_unload(comp, dobj);

	/*
	 * We don't free the link here as what remove_link() do since BE
	 * links are not allocated by topology.
	 * We however need to reset the dobj type to its initial values
	 */
	dobj->type = SND_SOC_DOBJ_NONE;
	list_del(&dobj->list);
}