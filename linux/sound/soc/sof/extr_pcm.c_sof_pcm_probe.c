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
struct snd_sof_pdata {int /*<<< orphan*/  tplg_filename; int /*<<< orphan*/  tplg_filename_prefix; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; struct snd_soc_component* component; struct snd_sof_pdata* pdata; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_resume; int /*<<< orphan*/  runtime_suspend; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_sof_load_topology (struct snd_sof_dev*,char const*) ; 
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 

__attribute__((used)) static int sof_pcm_probe(struct snd_soc_component *component)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pdata *plat_data = sdev->pdata;
	const char *tplg_filename;
	int ret;

	/* load the default topology */
	sdev->component = component;

	tplg_filename = devm_kasprintf(sdev->dev, GFP_KERNEL,
				       "%s/%s",
				       plat_data->tplg_filename_prefix,
				       plat_data->tplg_filename);
	if (!tplg_filename)
		return -ENOMEM;

	ret = snd_sof_load_topology(sdev, tplg_filename);
	if (ret < 0) {
		dev_err(sdev->dev, "error: failed to load DSP topology %d\n",
			ret);
		return ret;
	}

	/*
	 * Some platforms in SOF, ex: BYT, may not have their platform PM
	 * callbacks set. Increment the usage count so as to
	 * prevent the device from entering runtime suspend.
	 */
	if (!sof_ops(sdev)->runtime_suspend || !sof_ops(sdev)->runtime_resume)
		pm_runtime_get_noresume(sdev->dev);

	return ret;
}