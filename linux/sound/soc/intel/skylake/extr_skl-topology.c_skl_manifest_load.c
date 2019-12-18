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
struct TYPE_2__ {scalar_t__ size; } ;
struct snd_soc_tplg_manifest {TYPE_1__ priv; } ;
struct snd_soc_component {int dummy; } ;
struct skl_dev {scalar_t__ lib_count; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SKL_MAX_LIB ; 
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  skl_tplg_get_manifest_data (struct snd_soc_tplg_manifest*,int /*<<< orphan*/ ,struct skl_dev*) ; 
 struct hdac_bus* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int skl_manifest_load(struct snd_soc_component *cmpnt, int index,
				struct snd_soc_tplg_manifest *manifest)
{
	struct hdac_bus *bus = snd_soc_component_get_drvdata(cmpnt);
	struct skl_dev *skl = bus_to_skl(bus);

	/* proceed only if we have private data defined */
	if (manifest->priv.size == 0)
		return 0;

	skl_tplg_get_manifest_data(manifest, bus->dev, skl);

	if (skl->lib_count > SKL_MAX_LIB) {
		dev_err(bus->dev, "Exceeding max Library count. Got:%d\n",
					skl->lib_count);
		return  -EINVAL;
	}

	return 0;
}