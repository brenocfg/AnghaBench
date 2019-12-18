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
struct soc_tplg {scalar_t__ pass; int /*<<< orphan*/  dev; scalar_t__ pos; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_dai {TYPE_1__ priv; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOC_TPLG_PASS_BE_DAI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_tplg_dai_config (struct soc_tplg*,struct snd_soc_tplg_dai*) ; 

__attribute__((used)) static int soc_tplg_dai_elems_load(struct soc_tplg *tplg,
				   struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_dai *dai;
	int count;
	int i;

	count = le32_to_cpu(hdr->count);

	if (tplg->pass != SOC_TPLG_PASS_BE_DAI)
		return 0;

	/* config the existing BE DAIs */
	for (i = 0; i < count; i++) {
		dai = (struct snd_soc_tplg_dai *)tplg->pos;
		if (le32_to_cpu(dai->size) != sizeof(*dai)) {
			dev_err(tplg->dev, "ASoC: invalid physical DAI size\n");
			return -EINVAL;
		}

		soc_tplg_dai_config(tplg, dai);
		tplg->pos += (sizeof(*dai) + le32_to_cpu(dai->priv.size));
	}

	dev_dbg(tplg->dev, "ASoC: Configure %d BE DAIs\n", count);
	return 0;
}