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
struct soc_tplg {scalar_t__ pass; int /*<<< orphan*/  dev; scalar_t__ pos; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  count; } ;
struct snd_soc_tplg_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOC_TPLG_PASS_WIDGET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int soc_tplg_dapm_widget_create (struct soc_tplg*,struct snd_soc_tplg_dapm_widget*) ; 

__attribute__((used)) static int soc_tplg_dapm_widget_elems_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	struct snd_soc_tplg_dapm_widget *widget;
	int ret, count, i;

	count = le32_to_cpu(hdr->count);

	if (tplg->pass != SOC_TPLG_PASS_WIDGET)
		return 0;

	dev_dbg(tplg->dev, "ASoC: adding %d DAPM widgets\n", count);

	for (i = 0; i < count; i++) {
		widget = (struct snd_soc_tplg_dapm_widget *) tplg->pos;
		if (le32_to_cpu(widget->size) != sizeof(*widget)) {
			dev_err(tplg->dev, "ASoC: invalid widget size\n");
			return -EINVAL;
		}

		ret = soc_tplg_dapm_widget_create(tplg, widget);
		if (ret < 0) {
			dev_err(tplg->dev, "ASoC: failed to load widget %s\n",
				widget->name);
			return ret;
		}
	}

	return 0;
}