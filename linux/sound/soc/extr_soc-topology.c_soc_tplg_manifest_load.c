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
struct soc_tplg {scalar_t__ pass; int /*<<< orphan*/  index; scalar_t__ comp; TYPE_1__* ops; scalar_t__ pos; } ;
struct snd_soc_tplg_manifest {int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_hdr {int dummy; } ;
struct TYPE_2__ {int (* manifest ) (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_tplg_manifest*) ;} ;

/* Variables and functions */
 scalar_t__ SOC_TPLG_PASS_MANIFEST ; 
 int /*<<< orphan*/  kfree (struct snd_soc_tplg_manifest*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int manifest_new_ver (struct soc_tplg*,struct snd_soc_tplg_manifest*,struct snd_soc_tplg_manifest**) ; 
 int stub1 (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_tplg_manifest*) ; 

__attribute__((used)) static int soc_tplg_manifest_load(struct soc_tplg *tplg,
				  struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_manifest *manifest, *_manifest;
	bool abi_match;
	int err;

	if (tplg->pass != SOC_TPLG_PASS_MANIFEST)
		return 0;

	manifest = (struct snd_soc_tplg_manifest *)tplg->pos;

	/* check ABI version by size, create a new manifest if abi not match */
	if (le32_to_cpu(manifest->size) == sizeof(*manifest)) {
		abi_match = true;
		_manifest = manifest;
	} else {
		abi_match = false;
		err = manifest_new_ver(tplg, manifest, &_manifest);
		if (err < 0)
			return err;
	}

	/* pass control to component driver for optional further init */
	if (tplg->comp && tplg->ops && tplg->ops->manifest)
		return tplg->ops->manifest(tplg->comp, tplg->index, _manifest);

	if (!abi_match)	/* free the duplicated one */
		kfree(_manifest);

	return 0;
}