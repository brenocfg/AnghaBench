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
struct soc_tplg {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
struct snd_soc_tplg_manifest_v4 {TYPE_2__ priv; int /*<<< orphan*/  dai_link_elems; int /*<<< orphan*/  pcm_elems; int /*<<< orphan*/  graph_elems; int /*<<< orphan*/  widget_elems; int /*<<< orphan*/  control_elems; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  data; } ;
struct snd_soc_tplg_manifest {int size; TYPE_1__ priv; int /*<<< orphan*/  dai_link_elems; int /*<<< orphan*/  pcm_elems; int /*<<< orphan*/  graph_elems; int /*<<< orphan*/  widget_elems; int /*<<< orphan*/  control_elems; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_soc_tplg_manifest* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int manifest_new_ver(struct soc_tplg *tplg,
			    struct snd_soc_tplg_manifest *src,
			    struct snd_soc_tplg_manifest **manifest)
{
	struct snd_soc_tplg_manifest *dest;
	struct snd_soc_tplg_manifest_v4 *src_v4;
	int size;

	*manifest = NULL;

	size = le32_to_cpu(src->size);
	if (size != sizeof(*src_v4)) {
		dev_warn(tplg->dev, "ASoC: invalid manifest size %d\n",
			 size);
		if (size)
			return -EINVAL;
		src->size = cpu_to_le32(sizeof(*src_v4));
	}

	dev_warn(tplg->dev, "ASoC: old version of manifest\n");

	src_v4 = (struct snd_soc_tplg_manifest_v4 *)src;
	dest = kzalloc(sizeof(*dest) + le32_to_cpu(src_v4->priv.size),
		       GFP_KERNEL);
	if (!dest)
		return -ENOMEM;

	dest->size = cpu_to_le32(sizeof(*dest)); /* size of latest abi version */
	dest->control_elems = src_v4->control_elems;
	dest->widget_elems = src_v4->widget_elems;
	dest->graph_elems = src_v4->graph_elems;
	dest->pcm_elems = src_v4->pcm_elems;
	dest->dai_link_elems = src_v4->dai_link_elems;
	dest->priv.size = src_v4->priv.size;
	if (dest->priv.size)
		memcpy(dest->priv.data, src_v4->priv.data,
		       le32_to_cpu(src_v4->priv.size));

	*manifest = dest;
	return 0;
}