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
struct snd_soc_tplg_pcm_v4 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_pcm {TYPE_1__ priv; int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  payload_size; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOC_TPLG_PASS_PCM_DAI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_tplg_pcm*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_new_ver (struct soc_tplg*,struct snd_soc_tplg_pcm*,struct snd_soc_tplg_pcm**) ; 
 scalar_t__ soc_tplg_check_elem_count (struct soc_tplg*,int,int,int,char*) ; 
 int /*<<< orphan*/  soc_tplg_pcm_create (struct soc_tplg*,struct snd_soc_tplg_pcm*) ; 

__attribute__((used)) static int soc_tplg_pcm_elems_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_pcm *pcm, *_pcm;
	int count;
	int size;
	int i;
	bool abi_match;

	count = le32_to_cpu(hdr->count);

	if (tplg->pass != SOC_TPLG_PASS_PCM_DAI)
		return 0;

	/* check the element size and count */
	pcm = (struct snd_soc_tplg_pcm *)tplg->pos;
	size = le32_to_cpu(pcm->size);
	if (size > sizeof(struct snd_soc_tplg_pcm)
		|| size < sizeof(struct snd_soc_tplg_pcm_v4)) {
		dev_err(tplg->dev, "ASoC: invalid size %d for PCM elems\n",
			size);
		return -EINVAL;
	}

	if (soc_tplg_check_elem_count(tplg,
				      size, count,
				      le32_to_cpu(hdr->payload_size),
				      "PCM DAI")) {
		dev_err(tplg->dev, "ASoC: invalid count %d for PCM DAI elems\n",
			count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		pcm = (struct snd_soc_tplg_pcm *)tplg->pos;
		size = le32_to_cpu(pcm->size);

		/* check ABI version by size, create a new version of pcm
		 * if abi not match.
		 */
		if (size == sizeof(*pcm)) {
			abi_match = true;
			_pcm = pcm;
		} else {
			abi_match = false;
			pcm_new_ver(tplg, pcm, &_pcm);
		}

		/* create the FE DAIs and DAI links */
		soc_tplg_pcm_create(tplg, _pcm);

		/* offset by version-specific struct size and
		 * real priv data size
		 */
		tplg->pos += size + le32_to_cpu(_pcm->priv.size);

		if (!abi_match)
			kfree(_pcm); /* free the duplicated one */
	}

	dev_dbg(tplg->dev, "ASoC: adding %d PCM DAIs\n", count);

	return 0;
}