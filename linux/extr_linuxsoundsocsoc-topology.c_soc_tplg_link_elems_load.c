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
struct soc_tplg {scalar_t__ pass; scalar_t__ pos; int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_link_config_v4 {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct snd_soc_tplg_link_config {int size; TYPE_1__ priv; } ;
struct snd_soc_tplg_hdr {int count; scalar_t__ payload_size; scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOC_TPLG_PASS_LINK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_tplg_link_config*) ; 
 int link_new_ver (struct soc_tplg*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_link_config**) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,int,scalar_t__,char*) ; 
 int soc_tplg_link_config (struct soc_tplg*,struct snd_soc_tplg_link_config*) ; 

__attribute__((used)) static int soc_tplg_link_elems_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_link_config *link, *_link;
	int count = hdr->count;
	int i, ret;
	bool abi_match;

	if (tplg->pass != SOC_TPLG_PASS_LINK) {
		tplg->pos += hdr->size + hdr->payload_size;
		return 0;
	};

	/* check the element size and count */
	link = (struct snd_soc_tplg_link_config *)tplg->pos;
	if (link->size > sizeof(struct snd_soc_tplg_link_config)
		|| link->size < sizeof(struct snd_soc_tplg_link_config_v4)) {
		dev_err(tplg->dev, "ASoC: invalid size %d for physical link elems\n",
			link->size);
		return -EINVAL;
	}

	if (soc_tplg_check_elem_count(tplg,
		link->size, count,
		hdr->payload_size, "physical link config")) {
		dev_err(tplg->dev, "ASoC: invalid count %d for physical link elems\n",
			count);
		return -EINVAL;
	}

	/* config physical DAI links */
	for (i = 0; i < count; i++) {
		link = (struct snd_soc_tplg_link_config *)tplg->pos;
		if (link->size == sizeof(*link)) {
			abi_match = true;
			_link = link;
		} else {
			abi_match = false;
			ret = link_new_ver(tplg, link, &_link);
			if (ret < 0)
				return ret;
		}

		ret = soc_tplg_link_config(tplg, _link);
		if (ret < 0)
			return ret;

		/* offset by version-specific struct size and
		 * real priv data size
		 */
		tplg->pos += link->size + _link->priv.size;

		if (!abi_match)
			kfree(_link); /* free the duplicated one */
	}

	return 0;
}