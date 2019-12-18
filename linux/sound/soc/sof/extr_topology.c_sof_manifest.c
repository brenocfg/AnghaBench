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
typedef  scalar_t__ u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;
struct snd_soc_tplg_manifest {TYPE_1__ priv; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_SOC_SOF_STRICT_ABI_CHECKS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOF_ABI_MAJOR ; 
 int /*<<< orphan*/  SOF_ABI_MINOR ; 
 int /*<<< orphan*/  SOF_ABI_PATCH ; 
 scalar_t__ SOF_ABI_VER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOF_ABI_VERSION ; 
 scalar_t__ SOF_ABI_VERSION_INCOMPATIBLE (scalar_t__,scalar_t__) ; 
 scalar_t__ SOF_TPLG_ABI_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int sof_manifest(struct snd_soc_component *scomp, int index,
			struct snd_soc_tplg_manifest *man)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	u32 size;
	u32 abi_version;

	size = le32_to_cpu(man->priv.size);

	/* backward compatible with tplg without ABI info */
	if (!size) {
		dev_dbg(sdev->dev, "No topology ABI info\n");
		return 0;
	}

	if (size != SOF_TPLG_ABI_SIZE) {
		dev_err(sdev->dev, "error: invalid topology ABI size\n");
		return -EINVAL;
	}

	dev_info(sdev->dev,
		 "Topology: ABI %d:%d:%d Kernel ABI %d:%d:%d\n",
		 man->priv.data[0], man->priv.data[1],
		 man->priv.data[2], SOF_ABI_MAJOR, SOF_ABI_MINOR,
		 SOF_ABI_PATCH);

	abi_version = SOF_ABI_VER(man->priv.data[0],
				  man->priv.data[1],
				  man->priv.data[2]);

	if (SOF_ABI_VERSION_INCOMPATIBLE(SOF_ABI_VERSION, abi_version)) {
		dev_err(sdev->dev, "error: incompatible topology ABI version\n");
		return -EINVAL;
	}

	if (abi_version > SOF_ABI_VERSION) {
		if (!IS_ENABLED(CONFIG_SND_SOC_SOF_STRICT_ABI_CHECKS)) {
			dev_warn(sdev->dev, "warn: topology ABI is more recent than kernel\n");
		} else {
			dev_err(sdev->dev, "error: topology ABI is more recent than kernel\n");
			return -EINVAL;
		}
	}

	return 0;
}