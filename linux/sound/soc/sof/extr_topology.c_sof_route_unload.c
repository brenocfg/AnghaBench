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
struct snd_sof_route {int /*<<< orphan*/  list; struct snd_sof_route* private; } ;
struct snd_soc_dobj {struct snd_sof_route* private; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sof_route*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sof_route_unload(struct snd_soc_component *scomp,
			    struct snd_soc_dobj *dobj)
{
	struct snd_sof_route *sroute;

	sroute = dobj->private;
	if (!sroute)
		return 0;

	/* free sroute and its private data */
	kfree(sroute->private);
	list_del(&sroute->list);
	kfree(sroute);

	return 0;
}