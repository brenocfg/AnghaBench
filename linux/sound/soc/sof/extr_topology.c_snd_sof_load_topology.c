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
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  component; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SND_SOC_TPLG_INDEX_ALL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int snd_soc_tplg_component_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct firmware const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sof_tplg_ops ; 

int snd_sof_load_topology(struct snd_sof_dev *sdev, const char *file)
{
	const struct firmware *fw;
	int ret;

	dev_dbg(sdev->dev, "loading topology:%s\n", file);

	ret = request_firmware(&fw, file, sdev->dev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: tplg request firmware %s failed err: %d\n",
			file, ret);
		return ret;
	}

	ret = snd_soc_tplg_component_load(sdev->component,
					  &sof_tplg_ops, fw,
					  SND_SOC_TPLG_INDEX_ALL);
	if (ret < 0) {
		dev_err(sdev->dev, "error: tplg component load failed %d\n",
			ret);
		ret = -EINVAL;
	}

	release_firmware(fw);
	return ret;
}