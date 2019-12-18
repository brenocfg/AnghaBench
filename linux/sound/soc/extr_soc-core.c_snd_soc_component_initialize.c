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
struct snd_soc_component_driver {int dummy; } ;
struct snd_soc_component {struct snd_soc_component_driver const* driver; struct device* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  card_list; int /*<<< orphan*/  dobj_list; int /*<<< orphan*/  dai_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  fmt_single_name (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_soc_component_initialize(struct snd_soc_component *component,
	const struct snd_soc_component_driver *driver, struct device *dev)
{
	INIT_LIST_HEAD(&component->dai_list);
	INIT_LIST_HEAD(&component->dobj_list);
	INIT_LIST_HEAD(&component->card_list);
	mutex_init(&component->io_mutex);

	component->name = fmt_single_name(dev, &component->id);
	if (!component->name) {
		dev_err(dev, "ASoC: Failed to allocate name\n");
		return -ENOMEM;
	}

	component->dev = dev;
	component->driver = driver;

	return 0;
}