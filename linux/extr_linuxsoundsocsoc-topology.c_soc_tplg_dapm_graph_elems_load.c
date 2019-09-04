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
struct soc_tplg {scalar_t__ pass; scalar_t__ pos; int /*<<< orphan*/  dev; TYPE_1__* comp; } ;
struct snd_soc_tplg_hdr {int count; int /*<<< orphan*/  index; scalar_t__ payload_size; scalar_t__ size; } ;
struct snd_soc_tplg_dapm_graph_elem {int /*<<< orphan*/ * control; int /*<<< orphan*/ * sink; int /*<<< orphan*/ * source; } ;
struct snd_soc_dapm_route {int /*<<< orphan*/ * control; int /*<<< orphan*/ * connected; int /*<<< orphan*/ * sink; int /*<<< orphan*/ * source; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct TYPE_2__ {struct snd_soc_dapm_context dapm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 scalar_t__ SOC_TPLG_PASS_GRAPH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,struct snd_soc_dapm_route*,int) ; 
 int /*<<< orphan*/  soc_tplg_add_route (struct soc_tplg*,struct snd_soc_dapm_route*) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,int,scalar_t__,char*) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int soc_tplg_dapm_graph_elems_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_dapm_context *dapm = &tplg->comp->dapm;
	struct snd_soc_dapm_route route;
	struct snd_soc_tplg_dapm_graph_elem *elem;
	int count = hdr->count, i;

	if (tplg->pass != SOC_TPLG_PASS_GRAPH) {
		tplg->pos += hdr->size + hdr->payload_size;
		return 0;
	}

	if (soc_tplg_check_elem_count(tplg,
		sizeof(struct snd_soc_tplg_dapm_graph_elem),
		count, hdr->payload_size, "graph")) {

		dev_err(tplg->dev, "ASoC: invalid count %d for DAPM routes\n",
			count);
		return -EINVAL;
	}

	dev_dbg(tplg->dev, "ASoC: adding %d DAPM routes for index %d\n", count,
		hdr->index);

	for (i = 0; i < count; i++) {
		elem = (struct snd_soc_tplg_dapm_graph_elem *)tplg->pos;
		tplg->pos += sizeof(struct snd_soc_tplg_dapm_graph_elem);

		/* validate routes */
		if (strnlen(elem->source, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;
		if (strnlen(elem->sink, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;
		if (strnlen(elem->control, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			return -EINVAL;

		route.source = elem->source;
		route.sink = elem->sink;
		route.connected = NULL; /* set to NULL atm for tplg users */
		if (strnlen(elem->control, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) == 0)
			route.control = NULL;
		else
			route.control = elem->control;

		soc_tplg_add_route(tplg, &route);

		/* add route, but keep going if some fail */
		snd_soc_dapm_add_routes(dapm, &route, 1);
	}

	return 0;
}