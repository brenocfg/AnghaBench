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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ private; } ;
struct soc_bytes_ext {TYPE_1__ dobj; } ;
struct snd_soc_dapm_widget {int num_kcontrols; struct snd_kcontrol_new* kcontrol_news; struct skl_module_cfg* priv; } ;
struct snd_kcontrol_new {int access; scalar_t__ private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  caps_size; int /*<<< orphan*/ * caps; } ;
struct skl_module_cfg {TYPE_2__ formats_config; } ;
struct skl_algo_data {scalar_t__ set_params; int /*<<< orphan*/  size; scalar_t__ params; } ;

/* Variables and functions */
 scalar_t__ SKL_PARAM_INIT ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 

__attribute__((used)) static int skl_tplg_set_module_init_data(struct snd_soc_dapm_widget *w)
{
	const struct snd_kcontrol_new *k;
	struct soc_bytes_ext *sb;
	struct skl_algo_data *bc;
	struct skl_module_cfg *mconfig = w->priv;
	int i;

	for (i = 0; i < w->num_kcontrols; i++) {
		k = &w->kcontrol_news[i];
		if (k->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) {
			sb = (struct soc_bytes_ext *)k->private_value;
			bc = (struct skl_algo_data *)sb->dobj.private;

			if (bc->set_params != SKL_PARAM_INIT)
				continue;

			mconfig->formats_config.caps = (u32 *)bc->params;
			mconfig->formats_config.caps_size = bc->size;

			break;
		}
	}

	return 0;
}