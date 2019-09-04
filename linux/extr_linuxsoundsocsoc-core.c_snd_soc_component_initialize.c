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
struct snd_soc_dapm_context {int idle_bias_off; int /*<<< orphan*/  set_bias_level; int /*<<< orphan*/  stream_event; int /*<<< orphan*/  seq_notifier; int /*<<< orphan*/  suspend_bias_off; int /*<<< orphan*/  bias_level; struct snd_soc_component* component; struct device* dev; } ;
struct snd_soc_component_driver {scalar_t__ set_bias_level; scalar_t__ stream_event; scalar_t__ seq_notifier; int /*<<< orphan*/  suspend_bias_off; int /*<<< orphan*/  idle_bias_on; } ;
struct snd_soc_component {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  dai_list; struct snd_soc_component_driver const* driver; struct device* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  fmt_single_name (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_seq_notifier ; 
 int /*<<< orphan*/  snd_soc_component_set_bias_level ; 
 int /*<<< orphan*/  snd_soc_component_stream_event ; 

__attribute__((used)) static int snd_soc_component_initialize(struct snd_soc_component *component,
	const struct snd_soc_component_driver *driver, struct device *dev)
{
	struct snd_soc_dapm_context *dapm;

	component->name = fmt_single_name(dev, &component->id);
	if (!component->name) {
		dev_err(dev, "ASoC: Failed to allocate name\n");
		return -ENOMEM;
	}

	component->dev = dev;
	component->driver = driver;

	dapm = snd_soc_component_get_dapm(component);
	dapm->dev = dev;
	dapm->component = component;
	dapm->bias_level = SND_SOC_BIAS_OFF;
	dapm->idle_bias_off = !driver->idle_bias_on;
	dapm->suspend_bias_off = driver->suspend_bias_off;
	if (driver->seq_notifier)
		dapm->seq_notifier = snd_soc_component_seq_notifier;
	if (driver->stream_event)
		dapm->stream_event = snd_soc_component_stream_event;
	if (driver->set_bias_level)
		dapm->set_bias_level = snd_soc_component_set_bias_level;

	INIT_LIST_HEAD(&component->dai_list);
	mutex_init(&component->io_mutex);

	return 0;
}