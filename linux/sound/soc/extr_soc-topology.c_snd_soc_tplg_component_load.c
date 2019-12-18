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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tplg ;
struct soc_tplg {int /*<<< orphan*/  bytes_ext_ops_count; int /*<<< orphan*/  bytes_ext_ops; int /*<<< orphan*/  io_ops_count; int /*<<< orphan*/  io_ops; int /*<<< orphan*/  req_index; struct snd_soc_tplg_ops* ops; struct snd_soc_component* comp; int /*<<< orphan*/  dev; struct firmware const* fw; } ;
struct snd_soc_tplg_ops {int /*<<< orphan*/  bytes_ext_ops_count; int /*<<< orphan*/  bytes_ext_ops; int /*<<< orphan*/  io_ops_count; int /*<<< orphan*/  io_ops; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_TPLG_INDEX_ALL ; 
 int /*<<< orphan*/  memset (struct soc_tplg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_tplg_component_remove (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int soc_tplg_load (struct soc_tplg*) ; 

int snd_soc_tplg_component_load(struct snd_soc_component *comp,
	struct snd_soc_tplg_ops *ops, const struct firmware *fw, u32 id)
{
	struct soc_tplg tplg;
	int ret;

	/* setup parsing context */
	memset(&tplg, 0, sizeof(tplg));
	tplg.fw = fw;
	tplg.dev = comp->dev;
	tplg.comp = comp;
	tplg.ops = ops;
	tplg.req_index = id;
	tplg.io_ops = ops->io_ops;
	tplg.io_ops_count = ops->io_ops_count;
	tplg.bytes_ext_ops = ops->bytes_ext_ops;
	tplg.bytes_ext_ops_count = ops->bytes_ext_ops_count;

	ret = soc_tplg_load(&tplg);
	/* free the created components if fail to load topology */
	if (ret)
		snd_soc_tplg_component_remove(comp, SND_SOC_TPLG_INDEX_ALL);

	return ret;
}